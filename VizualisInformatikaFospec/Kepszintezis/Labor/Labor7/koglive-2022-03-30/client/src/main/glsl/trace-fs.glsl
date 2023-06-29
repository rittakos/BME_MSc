#version 300 es 
precision highp float;
precision highp sampler3D;


uniform struct {
  vec3 position;
  mat4 rayDirMatrix;
} camera;

uniform struct {
  vec4 position;
  vec4 powerDensity;
} lights[2];

uniform struct{
  samplerCube env;
  sampler3D volume;
} scene;

in vec2 tex;
in vec4 rayDir;

out vec4 fragmentColor;

const float epsilon =  0.00001;

vec4 quatMult( vec4 q1, vec4 q2 ) {
   vec4 r;

   r.x   = q1.x * q2.x - dot( q1.yzw, q2.yzw );
   r.yzw = q1.x * q2.yzw + q2.x * q1.yzw + cross( q1.yzw, q2.yzw );

   return r;
}

vec4 quatSq( vec4 q ) {
   vec4 r;

   r.x   = q.x * q.x - dot( q.yzw, q.yzw );
   r.yzw = 2.0 * q.x * q.yzw;

   return r;
}

void iterateIntersect( inout vec4 q, inout vec4 qp) {
   for( int i = 0; i < 10; i++ ) {
      qp = 2.0 * quatMult(q, qp);
      q = quatSq(q) + vec4(1, 0.5, -0.1, 0.3);

      if( dot( q, q ) > 7.0 ) {
         break;
      }
   }
}

float dist(vec3 p)
{
  vec4 z = vec4( p, 0.0 );
  vec4 zp = vec4( 1, 0.0, 0.0, 0.0 );
  iterateIntersect( z, zp );
  float normZ = length( z );
  return 0.5 * normZ * log( normZ ) / length( zp );
}

float sphereDist(vec3 p)
{
  const vec3 c = vec3( 0.0, 0.0, 0.0);
  const float r = 5.0; 
  return length(p - c) - r;
}

vec3 grad(vec3 p)
{
  return vec3 (dist(p + vec3(epsilon, 0.0, 0.0)) - dist(p - vec3(epsilon, 0.0, 0.0)),
               dist(p + vec3(0.0, epsilon, 0.0)) - dist(p - vec3(0.0, epsilon, 0.0)),
               dist(p + vec3(0.0, 0.0, epsilon)) - dist(p - vec3(0.0, 0.0, epsilon))); 
}


void main(void) {
  vec4 e = vec4(camera.position, 1);
  vec4 d = vec4(normalize(rayDir.xyz), 0);

  fragmentColor = vec4(0, 0, 0, 1);

  vec4 pos = e;

  // for(int idx = 0; idx < 150; ++idx)
  // {
  //   float minDis = sphereDist(pos.xyz);
  //   pos += d * minDis;
  //   if(minDis < epsilon)
  //   {
  //     vec4 normal = normalize (pos);
  //     fragmentColor.rgb = normal.rgb;
  //     return;
  //   }
  // }

  // for(int idx = 0; idx < 150; ++idx)
  // {
  //   float minDis = dist(pos.xyz);
  //   pos += d * minDis;
  //   if(minDis < epsilon)
  //   {
  //     vec3 normal = normalize(grad(pos.xyz));
  //     fragmentColor.rgb = normal.rgb;
  //     return;
  //   }
  // }

  for(int idx = 0; idx < 150; ++idx) // csak egy kockan belul legyen
  {
    e += d * 0.1;
    float voxel = texture(scene.volume, e.xyz).r;
    if(voxel > 0.2) //lehessen valtoztatni
    {
      fragmentColor = vec4(voxel, 0.0, 0.0, 1.0);
      return;
    }
  }

  fragmentColor.rgb += texture(scene.env, d.xyz).rgb;
}