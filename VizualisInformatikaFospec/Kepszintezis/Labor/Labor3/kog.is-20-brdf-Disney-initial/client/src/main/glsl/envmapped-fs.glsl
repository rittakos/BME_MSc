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
  vec3 kr;
} material;

void main(void) {
  vec3 normal = normalize(worldNormal.xyz);  
  vec3 bitangent = cross(normal, worldTangent.xyz);
  vec3 tangent = cross(bitangent, normal);

  vec3 x = worldPosition.xyz / worldPosition.w;
  vec3 viewDir = normalize(camera.position - x);

  vec3 radianceToEye = vec3(0, 0, 0);
  radianceToEye += 
    material.kr * 
    texture(material.environment, reflect(-viewDir, normal)).rgb;

  fragmentColor = vec4(radianceToEye, 1);
}
