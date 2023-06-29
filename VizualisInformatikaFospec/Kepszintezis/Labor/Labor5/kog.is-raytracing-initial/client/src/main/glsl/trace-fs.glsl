#version 300 es 
precision highp float;

out vec4 fragmentColor;
in vec4 rayDir;

uniform struct {
	samplerCube envTexture;
} material;

uniform struct {
  vec3 position;
  mat4 rayDirMatrix;
} camera;

uniform struct {
  mat4 surface;
  mat4 clipper;
} quadrics[2];




float IntersectQuadric (vec4 e, vec4 d, mat4 A)
{
  float a = dot(d * A, d);
  float b = dot(d * A, e) + dot(e * A, d);
  float c = dot(e * A, e);

  float D = b * b - 4.0f * a * c;

  if(D < 0.0)
    return -1.0f;

  float t1 = (-b - sqrt(D)) / (2.0f * a);
  float t2 = (-b + sqrt(D)) / (2.0f * a);

  return (t1 < 0.0) ? t2 : ((t2 < 0.0) ? t1 : min(t1, t2));
}


float IntersectClippedQuadric(vec4 e, vec4 d, mat4 A, mat4 B)
{
  float a = dot(d * A, d);
  float b = dot(d * A, e) + dot(e * A, d);
  float c = dot(e * A, e);

  float D = b * b - 4.0f * a * c;

  if(D < 0.0)
    return -1.0f;

  float t1 = (-b - sqrt(D)) / (2.0f * a);
  float t2 = (-b + sqrt(D)) / (2.0f * a);

  vec4 r1 = e + d * t1;
  vec4 r2 = e + d * t2;

  if(dot(r1 * B, r1) > 0.0)
    t1 = -1.0;


  if(dot(r2 * B, r2) > 0.0)
    t2 = -1.0;

  return (t1 < 0.0) ? t2 : ((t2 < 0.0) ? t1 : min(t1, t2));
}

bool findBestHit(vec4 e, vec4 d, out float bestT, out int index)
{
  bool hitFound = false;
  bestT = 10000.0f;
  index = 0;
  for(int idx = 0; idx < 2; ++idx)
  {
    float newT = IntersectClippedQuadric(e, d, quadrics[idx].surface, quadrics[idx].clipper);
    if(newT > 0.0)
    {
      if(bestT > newT)
      {
        bestT = newT;
        index = idx;
        hitFound = true;
      }
    }
  }

  return hitFound;
}


void main1(void) {
  mat4 A = mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, -9 );

  mat4 B = mat4(1, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, -4);


	vec4 e = vec4(camera.position, 1);
	vec4 d = vec4(normalize(rayDir.xyz), 0); 

  //float t = IntersectQuadric(e, d, A);
  float t = IntersectClippedQuadric(e, d, A, B);

  if(t > 0.0f)
  {
    vec4 hit = e + d * t;
    vec3 normal = normalize((hit * A + A * hit).xyz);
    if(dot(d.xyz, normal) > 0.0)
      normal *= -1.0;
    fragmentColor = texture(material.envTexture, reflect(d.xyz, normal));
    //fragmentColor = texture(material.envTexture, rafract(d.xyz, normal)); //tores hazihoz
    //fragmentColor = vec4(0.5 * (normal + vec3(1.0)), 1.0f);
  }
  else
    fragmentColor = texture(material.envTexture, d.xyz);
}

void main2(void) {
	vec4 e = vec4(camera.position, 1);
	vec4 d = vec4(normalize(rayDir.xyz), 0); 

  float bestT = -1.0;
  int bestI = 0;
  if(findBestHit(e, d, bestT, bestI))
  {
    mat4 A = quadrics[bestI].surface;
    mat4 B = quadrics[bestI].clipper;
    float t = bestT;

    vec4 hit = e + d * t;
    vec3 normal = normalize((hit * A + A * hit).xyz);
    if(dot(d.xyz, normal) > 0.0)
      normal *= -1.0;
    fragmentColor = texture(material.envTexture, reflect(d.xyz, normal));
  } else
  {
    fragmentColor = texture(material.envTexture, d.xyz);
  }
}

void main (void){
  int repeatCount = 10;

  vec4 e = vec4(camera.position, 1);
	vec4 d = vec4(normalize(rayDir.xyz), 0); 
  float bestT = -1.0;
  int bestI = 0;

  for(int repeat = 0; repeat < repeatCount; ++repeat)
  {
    bool hitf = findBestHit(e, d, bestT, bestI);
    if(!hitf)
      break;
    
    mat4 A = quadrics[bestI].surface;
    mat4 B = quadrics[bestI].clipper;
    float t = bestT;

    vec4 hit = e + d * t;
    vec3 normal = normalize((hit * A + A * hit).xyz);
    if(dot(d.xyz, normal) > 0.0)
      normal *= -1.0;

    e = hit;
    e.xyz += normal * 0.001;
    d.xyz = reflect(d.xyz, normal);
  }
  fragmentColor = texture(material.envTexture, d.xyz);
}
