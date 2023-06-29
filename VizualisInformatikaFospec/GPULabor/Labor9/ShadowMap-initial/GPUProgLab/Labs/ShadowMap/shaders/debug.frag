#version 330

uniform sampler2D depthTexture;

in vec2 fTexCoord;
out vec4 outColor;

void main()
{
	outColor = vec4(texture(depthTexture, fTexCoord).rrr, 1.0);
}
