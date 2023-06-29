#version 300 es 
precision highp float;

uniform struct {
  vec3 position;
  mat4 rayDirMatrix;
} camera;

uniform struct {
  mat4 surface;
  mat4 clipper;
  int type;
  vec4 kd;
} quadrics[5];

uniform struct {
  vec4 position;
  vec3 powerDensity;
} lights[2];

uniform struct {
  samplerCube envTexture;
  //LABTODO: randoms
  vec4 randoms[64];
} scene;

//LABTODO: average frames
uniform struct {
  sampler2D previousFrame;
  int frameCount;
} program;


in vec2 tex;
in vec4 rayDir;

out vec4 fragmentColor;

float intersectQuadric(vec4 e, vec4 d, mat4 surface, mat4 clipper){
  float a = dot(d * surface, d);
  float b = dot(d * surface, e) + dot(e * surface, d);
  float c = dot(e * surface, e);

  if(abs(a) < 0.001){
  	float t = - c / b;
  	vec4 h = e + d*t;
  	if(dot(h * clipper, h) > 0.0) {
  	  t = -1.0;    
 		}
 		return t;
  }

  float discr = b*b - 4.0*a*c;
  if(discr < 0.0){
    return -1.0;
  }
  float t1 = (-b - sqrt(discr)) / (2.0 * a);
  float t2 = (-b + sqrt(discr)) / (2.0 * a);  

  vec4 h1 = e + d * t1;
  if(dot(h1 * clipper, h1) > 0.0) {
    t1 = -1.0;
  }

  vec4 h2 = e + d * t2;
  if(dot(h2 * clipper, h2) > 0.0) {
    t2 = -1.0;    
  }

  return (t1<0.0)?t2:((t2<0.0)?t1:min(t1, t2));
}

bool findBestHit(vec4 e, vec4 d, out float bestT, out int bestIndex){
  bestT = 1000000.0;
  for(int i=0; i<quadrics.length(); i++){
    float t = intersectQuadric(e, d, quadrics[i].surface, quadrics[i].clipper);
    if(t > 0.0 && t < bestT){
      bestT = t;
      bestIndex = i;
    }
  }
  if(bestT < 999999.0)
    return true;
  else
    return false; 
}

vec3 directLighting(vec3 x, vec3 n, vec3 v){
	vec3 reflectedRadiance = vec3(0, 0, 0);
	for(int i=0; i<lights.length(); i++){
    vec3 lightPos = lights[i].position.xyz;
    vec3 lightDiff = lightPos - x * lights[i].position.w;
    float lightDist = length(lightDiff);
    vec3 lightDir = lightDiff / lightDist;//normalize(vec3(1, 1, 1));

    vec4 eShadow = vec4(x + n * 0.01, 1);
    vec4 dShadow = vec4(lightDir, 0);    
    float shadowT;
    int shadowIndex;
    if(!findBestHit(eShadow, dShadow, shadowT, shadowIndex) ||
           shadowT * lights[i].position.w > lightDist) {

      vec3 lightPowerDensity = lights[i].powerDensity;
      lightPowerDensity /= lightDist * lightDist;
      vec3 diffuseCoeff = vec3(0.3, 0.3, 0);
      vec3 specularCoeff = vec3(0.0, 0.0, 0.0);
      float shininess = 15.0;
      float cosa = dot(n, lightDir);
      if(cosa < 0.0) {
        cosa = 0.0;
      } else {
        reflectedRadiance += lightPowerDensity * cosa * diffuseCoeff * quadrics[shadowIndex].kd.rgb;

        float cosb = dot(n, v);
        vec3 halfway = normalize(v + lightDir);
        float cosd = dot(halfway, n);

        if(quadrics[shadowIndex].type == 3)
        {
           specularCoeff = vec3(1.0, 1.0, 1.0) * pow(max(dot(halfway, n), 0.0), 3000.0);
        }

        if(cosd < 0.0)
        	cosd = 0.0;
          // lightPowerDensity * cosa * BRDF
        reflectedRadiance += lightPowerDensity * specularCoeff * pow(cosd, shininess) * cosa / max(cosa, cosb) * quadrics[shadowIndex].kd.rgb;
      }
    }
  }
  return reflectedRadiance;
}

const float refractIdx = 1.2;

void main(void) {
  vec4 e = vec4(camera.position, 1);
  vec4 d = vec4(normalize(rayDir.xyz), 0);

  bool inside = true;

  vec3 radianceToEye = vec3(0,0,0);
  vec3 w = vec3(1, 1, 1);

  for(int iBounce=0; iBounce<15; iBounce++){
    float t;
    int idx;
    if( findBestHit(e, d, t, idx)){
      vec4 hit = e + d * t;

      vec4 gradient = hit * quadrics[idx].surface + quadrics[idx].surface * hit;
      vec3 normal = normalize(gradient.xyz);
      float ior = 0.8;
      if(dot(normal, d.xyz) > 0.0){
  	    normal = -normal;
        ior = 1.0 / ior;
  	  }

  		
      radianceToEye += w * directLighting(hit.xyz, normal, -d.xyz);
      w *= vec3(0.9, 0.95, 0.9);
      e = hit + vec4(normal * 0.01, 0);

      if(quadrics[idx].type == 0) {
        vec3 reflDir = reflect(d.xyz, normal);
        d.xyz = reflDir;
      }else if (quadrics[idx].type == 2) {
        e = hit - vec4(normal * 0.01 * 2.0, 0);
        d.xyz = refract(d.xyz, normal, ior);
      } else if (quadrics[idx].type == 4) {
        if(abs(dot(d.xyz, normal)) < 0.6) { //reflect
          d.xyz = reflect(d.xyz, normal);
        }else if(abs(dot(d.xyz, normal)) > 0.6) { //refract
          e = hit - vec4(normal * 0.01 * 5.0, 0);
          d.xyz = refract(d.xyz, normal, ior);
        }else {
          d.xyz = normalize(normal + normalize(scene.randoms[iBounce].xyz));
        } 
        
      }else{
        d.xyz = normalize(normal + normalize(scene.randoms[iBounce].xyz));
      }

    } else {
      radianceToEye += w * texture ( scene.envTexture, d.xyz).rgb;
      break;
    }
  }
  //fragmentColor = vec4(radianceToEye /*LABTODO: average frames*/, 1);

  //fragmentColor = vec4(radianceToEye, 1) * 0.01 + texture(program.previousFrame, tex) * 0.99;
  float weight = 1.0 / float(program.frameCount);
  fragmentColor = vec4(radianceToEye, 1) * weight + texture(program.previousFrame, tex) * (1.0-weight);
}