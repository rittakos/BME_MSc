#version 300 es 
precision highp float;

out vec4 fragmentColor;
in vec4 texCoord;
in vec4 worldNormal;
in vec4 worldTangent;
in vec4 worldPosition;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;

uniform struct {
  vec4 position;
  vec3 powerDensity;
} lights[8];

uniform struct{
  samplerCube environment;
  vec3 baseColor;
  float roughness;
  float metallic;
  float specular;
  float subsurface;
  float sheen;
  float sheenTint;
  float clearcoat;
  float clearcoatGloss;
  float anisotropic;
} material;

struct S
{
  float H;
}s;

float schlickWeight(float cosa) {
  float m = clamp(1.0 - cosa, 0.0, 1.0);
  return (m * m) * (m * m) * m;
}

const float PI = 3.1415f;
vec3 Cspec0;

vec3 disneyDiffuse(float NdotL, float NdotV, float LdotH) {
  float schlick_l = schlickWeight(NdotL);
  float shlick_v = schlickWeight(NdotV);
  
  float Fd90 = 0.5 + 2.0 * LdotH*LdotH * material.roughness;
  float Fd = mix(1.0, Fd90, schlick_l)
              * mix(1.0, Fd90, shlick_v);
  
  return (1.0/PI) * Fd * Cspec0;
}


float GTR2(float NdotH, float a) {
  float a2 = a*a;
  float t = 1.0 + (a2-1.0)*NdotH*NdotH;
  return a2 / (PI * t*t);
}


float smithG_GGX(float NdotV, float alphaG) {
  float a = alphaG * alphaG;
  float b = NdotV * NdotV;
  return 1.0 / (abs(NdotV) + max(sqrt(a + b - a*b), 0.0001));
}

float GTR2_aniso(float NdotH, float HdotX, float HdotY, float ax, float ay) {
  float hax = HdotX/ax;
  float hay = HdotY/ay;
  float tmp = (hax*hax + hay*hay) + NdotH*NdotH;
  return 1.0 / (PI * ax*ay * tmp * tmp);
}

float smithG_GGX_aniso(float NdotV, float VdotX, float VdotY, float ax, float ay) {
  float vax = VdotX/ax;
  float vay = VdotY*ay;
  float tmp = vax*vax + vay*vay + NdotV*NdotV;

  return 1.0 / (NdotV + sqrt( tmp ));
}

vec3 disneyMicrofacetIsotropic(vec3 n, vec3 l, vec3 v, vec3 t, vec3 b) {
  
  vec3 H = (l + v) / 2.0f;
  float NdotL = dot(n, l);
  float NdotV = dot(n, v);
  float NdotH = dot(n, H);
  float LdotH = dot(l, H);
  
  float a = max(0.001, material.roughness*material.roughness);
  //float Ds = GTR2(NdotH, a);

  float FH = schlickWeight(LdotH);
  vec3 Fs = mix(Cspec0, vec3(1, 1, 1), FH);

  float Gs;
  //Gs  = smithG_GGX(NdotL, a);
  //Gs *= smithG_GGX(NdotV, a);

  float aspect = sqrt(1.-material.anisotropic*.9);
  float ax = max(0.001, material.roughness*material.roughness/aspect);
  float ay = max(0.001, material.roughness*material.roughness*aspect);
  float Ds = GTR2_aniso(NdotH, dot(H, t), dot(H, b), ax, ay);


  Gs  = smithG_GGX_aniso(NdotL, dot(l, t), dot(l, b), ax, ay);
  Gs *= smithG_GGX_aniso(NdotV, dot(v, t), dot(v, b), ax, ay);
    
  return Gs*Fs*Ds;   // nincs osztas 4*cosa*cosb-vel !!??!
}

vec3 disneySubsurface(float NdotL, float NdotV, float LdotH) {
    
  float schlick_l = schlickWeight(NdotL);
  float shlick_v = schlickWeight(NdotV);
  float Fss90 = LdotH*LdotH*material.roughness;
  float Fss = mix(1.0, Fss90, schlick_l) * mix(1.0, Fss90, shlick_v);
  float ss = 1.25 * (Fss * (1. / (NdotL + NdotV) - .5) + .5);
    
  return (1./PI) * ss * material.baseColor;
}

vec3 disneySheen(float LdotH) {
  float FH = schlickWeight(LdotH);
  float r = material.baseColor.r;
  float g = material.baseColor.g;
  float b = material.baseColor.b;
  return FH * material.sheen * material.baseColor / (r*0.3+g*0.6+b*0.1);
}

float GTR1(float NdotH, float a) {
  if (a >= 1.0) return 1.0/PI;
  float a2 = a*a;
  float t = 1.0 + (a2-1.0)*NdotH*NdotH;
  return (a2-1.0) / (PI*log(a2)*t);
}

float disneyClearcoat(float NdotL, float NdotV, float NdotH, float LdotH) {
  return 0.0;
  float gloss = mix(.1,.001,material.clearcoatGloss);
  float Dr = GTR1(abs(NdotH), gloss);
  float FH = schlickWeight(LdotH);
  float Fr = mix(.04, 1.0, FH);
  float Gr = smithG_GGX(NdotL, .25) * smithG_GGX(NdotV, .25);
  return material.clearcoat * Fr * Gr * Dr;
}


vec3 bsdf(vec3 n, vec3 l, vec3 v, vec3 t, vec3 b) {

  vec3 H = (l + v) / 2.0f;
  float NdotL = dot(n, l);
  float NdotV = dot(n, v);
  float NdotH = dot(n, H);
  float LdotH = dot(l, H);

  vec3 diffuse = (1.0 - material.metallic) * disneyDiffuse(NdotL, NdotV, LdotH);

  vec3 diffSub = (1.0 - material.subsurface) * diffuse + material.subsurface * disneySubsurface(NdotL, NdotV, LdotH);
  
  vec3 sheen = (1.0 - material.metallic) * disneySheen(LdotH);

  float c = disneyClearcoat(NdotL, NdotV, NdotH, LdotH);
  vec3 clearcoatVec = vec3(c, c, c);

  return clearcoatVec + sheen + diffSub + disneyMicrofacetIsotropic(n, l, v, t, b);
}

vec3 shade(
  vec3 powerDensity,
  vec3 normal,
  vec3 lightDir,
  vec3 viewDir,
  vec3 tangent,
  vec3 bitangent) {

  float cosa = clamp( dot(lightDir, normal), 0.0, 1.0);
  return powerDensity * cosa * bsdf(normal, lightDir, viewDir, tangent, bitangent);
}

void main(void) {
  vec3 normal = normalize(worldNormal.xyz);  
  vec3 bitangent = cross(normal, worldTangent.xyz);
  vec3 tangent = cross(bitangent, normal);

  vec3 x = worldPosition.xyz / worldPosition.w;
  vec3 viewDir = normalize(camera.position - x);

  Cspec0 = mix(
    material.specular * vec3(.16, .16, .16),
    material.baseColor,
    material.metallic);


  vec3 radianceToEye = vec3(0, 0, 0);
  for(int i=0; i<1; i++){
    vec3 lightDiff = lights[i].position.xyz -
                 x * lights[i].position.w;
    float lightDistSquared = dot(lightDiff, lightDiff);
    vec3 lightDir = lightDiff / sqrt(lightDistSquared);
    vec3 powerDensity = lights[i].powerDensity / lightDistSquared;

    radianceToEye += shade(
      powerDensity,
      normal,
      lightDir,
      viewDir,
      tangent,
      bitangent
    );
  }

  fragmentColor = vec4(radianceToEye, 1);

  

  //fragmentColor = disneyMicrofacetIsotropic(NdotL, NdotV, NdotH, LdotH);

}
