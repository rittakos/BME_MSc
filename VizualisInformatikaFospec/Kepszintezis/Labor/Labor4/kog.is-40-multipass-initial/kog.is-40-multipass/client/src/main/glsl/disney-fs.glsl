#version 300 es 
precision highp float;

const float PI = 3.14159265359;

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
  vec3  baseColor;
  float roughness;
  float metallic;
  float specular;
  vec3  specularTint;
  float anisotropic;
  float sheen;
  vec3  sheenTint;
  float subsurface;
  float clearcoat;
  float clearcoatGloss;
} material;

// Disney brdf's taken from here:: https://github.com/wdas/brdf/blob/master/src/brdfs/disney.brdf
float schlickWeight(float cosa) {
  float m = clamp(1.0 - cosa, 0.0, 1.0);
  return (m * m) * (m * m) * m;
}

float GTR1(float NdotH, float a) {
  if (a >= 1.0) return 1.0/PI;
  float a2 = a*a;
  float t = 1.0 + (a2-1.0)*NdotH*NdotH;
  return (a2-1.0) / (PI*log(a2)*t);
}

float GTR2(float NdotH, float a) {
  float a2 = a*a;
  float t = 1.0 + (a2-1.0)*NdotH*NdotH;
  return a2 / (PI * t*t);
}

float GTR2_aniso(float NdotH, float HdotX, float HdotY, float ax, float ay) {
  float hax = HdotX/ax;
  float hay = HdotY/ay;
  float tmp = (hax*hax + hay*hay) + NdotH*NdotH;
  return 1.0 / (PI * ax*ay * tmp * tmp);
}

float smithG_GGX(float NdotV, float alphaG) {
  float a = alphaG*alphaG;
  float b = NdotV*NdotV;
  return 1.0 / (abs(NdotV) + max(sqrt(a + b - a*b), 0.0001));
}

float smithG_GGX_aniso(float NdotV, float VdotX, float VdotY, float ax, float ay) {
  float vax = VdotX/ax;
  float vay = VdotY*ay;
  float tmp = vax*vax + vay*vay + NdotV*NdotV;

  return 1.0 / (NdotV + sqrt( tmp ));
}

vec3 disneyDiffuse(float NdotL, float NdotV, float LdotH) {
  float schlick_l = schlickWeight(NdotL);
  float shlick_v = schlickWeight(NdotV);
  
  float Fd90 = 0.5 + 2.0 * LdotH*LdotH * material.roughness;
  float Fd = mix(1.0, Fd90, schlick_l) * mix(1.0, Fd90, shlick_v);
  
  return (1.0/PI) * Fd * material.baseColor;
}

vec3 disneySubsurface(float NdotL, float NdotV, float LdotH) {
    
  float schlick_l = schlickWeight(NdotL);
  float shlick_v = schlickWeight(NdotV);
  float Fss90 = LdotH*LdotH*material.roughness;
  float Fss = mix(1.0, Fss90, schlick_l) * mix(1.0, Fss90, shlick_v);
  float ss = 1.25 * (Fss * (1. / (NdotL + NdotV) - .5) + .5);
    
  return (1./PI) * ss * material.baseColor;
}

vec3 disneyMicrofacetIsotropic(float NdotL, float NdotV, float NdotH, float LdotH) {
    
  float Cdlum = dot(vec3(0.3, 0.6, 0.1), material.baseColor);

  vec3 Ctint = Cdlum > 0.0 ? material.baseColor/Cdlum : vec3(1, 1, 1);
  vec3 Cspec0 = mix(material.specular *.08 * mix(vec3(1, 1, 1), Ctint, material.specularTint), material.baseColor, material.metallic);
    
  float a = max(0.001, material.roughness*material.roughness);
  float Ds = GTR2(NdotH, a);
  float FH = schlickWeight(LdotH);
  vec3 Fs = mix(Cspec0, vec3(1, 1, 1), FH);
  float Gs;
  Gs  = smithG_GGX(NdotL, a);
  Gs *= smithG_GGX(NdotV, a);
    
  return Gs*Fs*Ds;
}

vec3 disneyMicrofacetAnisotropic(float NdotL, float NdotV, float NdotH, float LdotH,
                                 vec3 L, vec3 V,
                                 vec3 H, vec3 X, vec3 Y) {
    
  float Cdlum = dot(vec3(0.3, 0.6, 0.1), material.baseColor);

  vec3 Ctint = Cdlum > 0.0 ? material.baseColor/Cdlum : vec3(1, 1, 1); // normalize lum. to isolate hue+sat
  vec3 Cspec0 = mix(
    material.specular *.08 * mix(vec3(1, 1, 1), Ctint, material.specularTint),
    material.baseColor,
    material.metallic);

  float aspect = sqrt(1.-material.anisotropic*.9);
  float ax = max(0.001, material.roughness*material.roughness/aspect);
  float ay = max(0.001, material.roughness*material.roughness*aspect);
  float Ds = GTR2_aniso(NdotH, dot(H, X), dot(H, Y), ax, ay);
  float FH = schlickWeight(LdotH);
  vec3 Fs = mix(Cspec0, vec3(1, 1, 1), FH);
  float Gs;
  Gs  = smithG_GGX_aniso(NdotL, dot(L, X), dot(L, Y), ax, ay);
  Gs *= smithG_GGX_aniso(NdotV, dot(V, X), dot(V, Y), ax, ay);
    
  return Gs*Fs*Ds;
}

float disneyClearcoat(float NdotL, float NdotV, float NdotH, float LdotH) {
  float gloss = mix(.1,.001,material.clearcoatGloss);
  float Dr = GTR1(abs(NdotH), gloss);
  float FH = schlickWeight(LdotH);
  float Fr = mix(.04, 1.0, FH);
  float Gr = smithG_GGX(NdotL, .25) * smithG_GGX(NdotV, .25);
    return material.clearcoat * Fr * Gr * Dr;
}

vec3 disneySheen(float LdotH) {
  float FH = schlickWeight(LdotH);
//  float Cdlum = dot(vec3(0.3, 0.6, 0.1), material.baseColor);
//
//  vec3 Ctint = Cdlum > 0.0 ? material.baseColor/Cdlum : vec3(1, 1, 1);
//  vec3 Csheen = mix(vec3(1, 1, 1), Ctint, material.sheenTint);
  vec3 Fsheen = FH * material.sheen * vec3(1, 1, 1);//Csheen;
  return Fsheen;
}

vec3 bsdf(vec3 n, vec3 l, vec3 v, vec3 t, vec3 b) {
  float NdotL = dot(n, l);
  float NdotV = dot(n, v);

  if(NdotL < 0.0 || NdotV < 0.0)
    return vec3(0, 0, 0);

  vec3 h = normalize(l+v);
  float NdotH = dot(n, h);
  float LdotH = dot(l, h);
    
  vec3 diffuse = disneyDiffuse(NdotL, NdotV, LdotH);
  vec3 subSurface = disneySubsurface(NdotL, NdotV, LdotH);
  vec3 glossy = disneyMicrofacetIsotropic(NdotL, NdotV, NdotH, LdotH/*, v, l, h, t, b*/) ;/// (4.0 * NdotL * NdotV);
  float clearcoat = disneyClearcoat(NdotL, NdotV, NdotH, LdotH);
  vec3 sheen = disneySheen(LdotH);

  return sheen;

  return (mix(diffuse, subSurface, material.subsurface) + sheen) * (1.0 - material.metallic) + glossy;
    
  return ( mix(diffuse, subSurface, material.subsurface) + sheen ) * (1.0 - material.metallic) + glossy + clearcoat;
}

vec3 shade(
  vec3 powerDensity,
  vec3 normal,
  vec3 lightDir,
  vec3 viewDir,
  vec3 tangent,
  vec3 bitangent) {

  float cosa =
    clamp( dot(lightDir, normal), 0.0, 1.0);
  return
    powerDensity * cosa * bsdf(normal, lightDir, viewDir, tangent, bitangent);
}

void main(void) {
  vec3 normal = normalize(worldNormal.xyz);  
  vec3 bitangent = cross(normal, worldTangent.xyz);
  vec3 tangent = cross(bitangent, normal);

  vec3 x = worldPosition.xyz / worldPosition.w;
  vec3 viewDir = normalize(camera.position - x);

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

}
