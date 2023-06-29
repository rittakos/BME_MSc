#version 330

layout (location = 0) in vec3 vPosition;

uniform mat4 lightViewProj;
uniform mat4 modelMatrix;

void main(void) {
	vec4 worldPosition = modelMatrix * vec4(vPosition, 1.0);
	gl_Position = lightViewProj * worldPosition;
}
