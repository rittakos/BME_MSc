#version 300 es
in vec4 vertexPosition;
in vec2 vertexTexCoord;
out vec2 texCoord;
out vec4 rayDir;
out vec4 vertexToLight;

uniform mat4 shadowMapMatrix;

uniform struct {
  mat4 rayDirMatrix;
} camera;

void main(void) {
  vertexToLight = shadowMapMatrix * vertexPosition;
  texCoord = vertexTexCoord;
  gl_Position = vertexPosition;
  gl_Position.z = 0.9999999;
  rayDir = vertexPosition * camera.rayDirMatrix;
}
