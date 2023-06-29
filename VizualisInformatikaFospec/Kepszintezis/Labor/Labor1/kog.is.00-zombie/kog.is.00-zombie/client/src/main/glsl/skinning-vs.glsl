#version 300 es
in vec4 vertexPosition;
in vec4 vertexTexCoord;
in vec4 vertexNormal;
in vec4 blendIndices;  
in vec4 blendWeights;
out vec4 texCoord; // passed to FS
out vec4 worldPosition;
out vec4 worldNormal;

uniform struct {
  float nBones;
} multiMesh;

uniform struct{
  mat4 modelMatrix;
  mat4 modelMatrixInverse;
  mat4 bones[256];
} gameObject;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;

void main(void) {
  uvec4 ui = uvec4(blendIndices);
  mat4 blendedm = 
    gameObject.bones[ui.x] * blendWeights.x +
    gameObject.bones[ui.y] * blendWeights.y +
    gameObject.bones[ui.z] * blendWeights.z +
    gameObject.bones[ui.w] * blendWeights.w;

  worldPosition = vertexPosition * blendedm * gameObject.modelMatrix;
  gl_Position =  worldPosition * camera.viewProjMatrix;

  worldNormal = vec4(vertexNormal.xyz, 0) * blendedm * gameObject.modelMatrixInverse;
  texCoord = vertexTexCoord;
}
