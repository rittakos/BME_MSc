#version 300 es
in vec4 vertexPosition;
in vec4 vertexTexCoord;
out vec4 texCoord;
out vec4 rayDir;

uniform struct {
  vec3 position;
  mat4 rayDirMatrix;
} camera;

void main(void) {
  texCoord = vertexTexCoord;
  gl_Position = vertexPosition;
  gl_Position.z = 0.99999;
  rayDir = vertexPosition * camera.rayDirMatrix;
}
