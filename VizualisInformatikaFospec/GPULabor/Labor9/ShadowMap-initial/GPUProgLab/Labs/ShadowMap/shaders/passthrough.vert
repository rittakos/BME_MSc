#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;


uniform mat4 modelMatrix;
uniform mat4 viewProjMatrix;

out vec2 texCoord;
out vec4 worldPos;

void main(void) {
	texCoord = vTexCoord;
	worldPos = modelMatrix * vec4(vPosition, 1.0);
	gl_Position = viewProjMatrix * worldPos;
}

