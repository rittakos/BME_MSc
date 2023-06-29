#version 150 core

in vec4 position;
in vec3 normal;
in vec2 texCoord;

out vec2 coord;

void main()
{
	coord = texCoord;	
	gl_Position = position;
}