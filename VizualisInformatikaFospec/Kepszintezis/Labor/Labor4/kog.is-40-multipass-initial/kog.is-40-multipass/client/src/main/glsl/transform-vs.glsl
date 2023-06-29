#version 300 es
in vec4 vertexPosition;
in vec4 vertexTexCoord;
in vec4 vertexNormal;
in vec4 vertexTangent;
in vec4 vertexBitangent;
out vec4 texCoord; // passed to FS
out vec4 worldPosition;
out vec4 worldNormal;
out vec4 worldTangent;
out vec4 worldBitangent;

uniform struct{
  mat4 modelMatrix;
  mat4 modelMatrixInverse;
} gameObject;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;

void main(void) {
  worldPosition = vertexPosition * gameObject.modelMatrix;
  gl_Position =  worldPosition * camera.viewProjMatrix;

  worldNormal = gameObject.modelMatrixInverse * vec4(vertexNormal.xyz, 0);
  worldTangent = vec4(vertexTangent.xyz, 0) * gameObject.modelMatrix;
//  worldBitangent = vec4(vertexBitangent.xyz, 0) * gameObject.modelMatrix;
  texCoord = vertexTexCoord;
}
