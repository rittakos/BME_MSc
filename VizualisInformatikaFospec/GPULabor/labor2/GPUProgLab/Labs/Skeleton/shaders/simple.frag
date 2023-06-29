#version 330

uniform sampler2D data;

in vec2 fTexCoord;
out vec4 outColor;

void main()
{
	outColor = texture(data, fTexCoord);
}
