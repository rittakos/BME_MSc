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
  vec3 ks;
  float shininess;
} material;

vec3 brdf(vec3 normal, vec3 lightDir, vec3 viewDir) 
{
    float cosDelta = clamp(dot(normalize(viewDir + lightDir), normal), 0.0f, 1.0f);
    float cosTheta = clamp(dot(normal, viewDir), 0.0f, 1.0f);
    float cosTheta2 = clamp(dot(normal, lightDir), 0.0f, 1.0f);
    return (material.ks * pow(cosDelta, material.shininess)) / (max(cosTheta, cosTheta2));
}

vec3 shade(vec3 powerDensity, vec3 normal, vec3 lightDir, vec3 viewDir) 
{
     float cosTheta2 = clamp(dot(normal, lightDir), 0.0f, 1.0f);
    return powerDensity * cosTheta2 * brdf(normal, lightDir, viewDir);
}


void main(void) {
  vec3 normal = normalize(worldNormal.xyz);  
  vec3 bitangent = cross(normal, worldTangent.xyz);
  vec3 tangent = cross(bitangent, normal);

  vec3 x = worldPosition.xyz / worldPosition.w;
  vec3 viewDir = normalize(camera.position - x);

  vec3 radianceToEye = vec3(0, 0, 0);

  for(int i = 0; i < 2; ++i)
  {
    vec3 lightDiff = lights[i].position.xyz - x * lights[i].position.w;
    float lightDistSquared = dot(lightDiff, lightDiff);
    vec3 lightDir = lightDiff / sqrt(lightDistSquared);
    vec3 powerDensity = lights[i].powerDensity / lightDistSquared;

    radianceToEye += shade(powerDensity, normal, lightDir, viewDir);
  }

  fragmentColor = vec4(radianceToEye, 1.0f);
}
