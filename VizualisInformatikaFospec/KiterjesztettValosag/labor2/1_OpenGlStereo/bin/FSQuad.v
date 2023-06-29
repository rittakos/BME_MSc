#version 150 core

in vec4 position;
out vec2 texCoord;

void main()
{
	texCoord =position.xy*0.5+0.5;		
	gl_Position = position;
}