#version 430

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vVelocity;
layout(location = 2) in vec4 vLife;

out vec4 gVelocity;
out vec4 gLife;

void main()
{
	gl_Position = vPosition;
	gVelocity = vVelocity;
	gLife = vLife;	
}