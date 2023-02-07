#version 150 core

uniform sampler2D textureMap;

in vec2 coord;
out vec4 FragColor[1];

void main()
{
	vec4 value = texture(textureMap, coord);
	FragColor[0] = value;	
	//float exp = 1.0 / 2.2;
	//FragColor[0] = vec4(pow(value.rgb, vec3(exp,exp,exp)), value.a);	
}