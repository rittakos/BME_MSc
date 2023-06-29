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
//  vec3 kd;
  float r0;
  float roughness;
  float kappa;
} material;

vec3 brdf(
  vec3 normal,
  vec3 lightDir,
  vec3 viewDir) {
  float cosa = max(0.0, dot(lightDir, normal));
  float cosb = max(0.0, dot(viewDir, normal));
  vec3 halfway = normalize(lightDir + viewDir);
  float cosd = max(0.0, dot(lightDir, halfway));
  float cosp = max(0.0, dot(normal, halfway));  

  // Fresnel reflectance
  float refl = pow(1.0 - cosd, 5.0);
  refl *= (1.0 - material.r0);
  refl += material.r0;

  // Microfacet distribution by Beckmann
  float m_squared = material.roughness * material.roughness;
  float r1 = 1.0 / (4.0 * m_squared * pow(cosp, 4.0));
  float r2 = (cosp * cosp - 1.0) / (m_squared * cosp * cosp);
  float D = r1 * exp(r2);

  // Geometric shadowing
  float g1 = (2.0 * cosp * cosb) / cosd;
  float g2 = (2.0 * cosp * cosa) / cosd;
  float G = min(1.0, min(g1, g2));

  return vec3(1, 1, 1) *  (refl * D * G) / (3.14 * cosa * cosb);   
}

vec3 shade(
  vec3 powerDensity,
  vec3 normal,
  vec3 lightDir,
  vec3 viewDir) {

  float cosa =
    clamp( dot(lightDir, normal), 0.0, 1.0);
  return
    powerDensity * cosa * brdf(normal, lightDir, viewDir);
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
      viewDir
    );
  }

  fragmentColor = vec4(radianceToEye, 1);

}
