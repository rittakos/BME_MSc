#version 430

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vVelocity;

out vec4 fVelocity;

void main()
{
	gl_Position = vPosition;
	fVelocity = vVelocity;
}