#version 300 es
in vec4 vertexPosition;
in vec4 vertexTexCoord;
out vec3 rayDir;

uniform struct {
    mat4 rayDirMatrix;
    vec3 position;
} camera;

void main(void) {
    gl_Position = vertexPosition;
    rayDir = (vertexPosition * camera.rayDirMatrix).xyz;
}
