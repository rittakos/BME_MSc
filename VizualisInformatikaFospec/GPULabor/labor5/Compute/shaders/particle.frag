#version 430

in vec4 fVelocity;

out vec4 outColor;

void main()
{
	outColor = vec4((fVelocity.xyz + 1.0) / 2.0, 1.0);
}