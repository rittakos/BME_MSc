#version 300 es
in vec4 vertexPosition;
in vec4 vertexTexCoord;
in vec4 vertexNormal;
in vec4 blendIndices;  
in vec4 blendWeights;
out vec4 texCoord;
out vec4 worldPosition;
out vec4 worldNormal;
out vec4 debugColor;

uniform struct {
  float nBones;
} multiMesh;

uniform struct{
  mat4 modelMatrix;
  mat4 modelMatrixInverse;
} gameObject;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;

uniform struct{
  mat4 bones[256];
  mat4 rigging[3];
} motion;


void main(void) {
  uvec4 ui = uvec4(blendIndices);

  mat4 blendedm = motion.bones[ui.x] * blendWeights.x + 
                  motion.bones[ui.y] * blendWeights.y +
                  motion.bones[ui.z] * blendWeights.z +
                  motion.bones[ui.w] * blendWeights.w;

  //mat4 blendedm = motion.rigging[ui.x] * motion.bones[ui.x] * blendWeights.x + 
  //                motion.rigging[ui.y] * motion.bones[ui.y] * blendWeights.y +
  //                motion.rigging[ui.z] * motion.bones[ui.z] * blendWeights.z +
  //                motion.rigging[ui.w] * motion.bones[ui.w] * blendWeights.w;

  worldPosition = vertexPosition * blendedm * gameObject.modelMatrix;
  //worldPosition = vertexPosition * gameObject.modelMatrix;
  //worldPosition = vertexPosition * gameObject.modelMatrix + vec4(1,1,1,0) * float(gl_InstanceID);
  gl_Position =  worldPosition * camera.viewProjMatrix;
  worldNormal = vec4(vertexNormal.xyz, 0) * gameObject.modelMatrixInverse;
  texCoord = vertexTexCoord * vec4(1, -1, 1, 1);

  debugColor[ui.x] = blendWeights[0];
  debugColor[ui.y] = blendWeights[1];
  debugColor[ui.z] = blendWeights[2];
  debugColor.a = 1.0;
}
