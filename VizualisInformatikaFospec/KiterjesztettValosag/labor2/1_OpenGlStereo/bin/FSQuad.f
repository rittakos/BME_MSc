#version 150 core

uniform sampler2D l_texture;
uniform sampler2D r_texture;
uniform int anaglyphMode;

in vec2 texCoord;
out vec4 FragColor[1];

vec3 Anaglyph_Red_Blue(vec3 RGB_L, vec3 RGB_R)
{
	float R = dot(RGB_L, vec3(0.299, 0.587, 0.114)) + dot(RGB_R, vec3(0, 0, 0));
	float G = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 0, 0));
	float B = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0.299, 0.587, 0.114));
	return vec3(R,G,B);
}

vec3 Anaglyph_Red_Cyan(vec3 RGB_L, vec3 RGB_R)
{
	float R = dot(RGB_L, vec3(0.299, 0.587, 0.114)) + dot(RGB_R, vec3(0, 0, 0));
	float G = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0.299, 0.587, 0.114));
	float B = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0.299, 0.587, 0.114));
	return vec3(R,G,B);
}

vec3 Anaglyph_Color(vec3 RGB_L, vec3 RGB_R)
{
	float R = dot(RGB_L, vec3(1, 0, 0)) + dot(RGB_R, vec3(0, 0, 0));
	float G = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 1, 0));
	float B = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 0, 1));
	return vec3(R,G,B);
}


vec3 Anaglyph_HalfColor(vec3 RGB_L, vec3 RGB_R)
{
	float R = dot(RGB_L, vec3(0.299, 0.587, 0.114)) + dot(RGB_R, vec3(0, 0, 0));
	float G = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 1, 0));
	float B = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 0, 1));
	return vec3(R,G,B);
}


vec3 Anaglyph_Optimized(vec3 RGB_L, vec3 RGB_R)
{
	float R = dot(RGB_L, vec3(0, 0.45, 1.05)) + dot(RGB_R, vec3(0, 0, 0));
	float G = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 1, 0));
	float B = dot(RGB_L, vec3(0, 0, 0)) + dot(RGB_R, vec3(0, 0, 1));
	return vec3(R,G,B);
}


vec3 Anaglyph_Dubois(vec3 RGB_L, vec3 RGB_R)
{
	float R = dot(RGB_L, vec3( 0.456, 0.5 , 0.76 )) + dot(RGB_R, vec3(-0.043, -0.088, -0.002));
	float G = dot(RGB_L, vec3(-0.04 , -0.038, -0.016)) + dot(RGB_R, vec3( 0.378, 0.734, -0.018));
	float B = dot(RGB_L, vec3(-0.015, -0.021, -0.005)) + dot(RGB_R, vec3(-0.072, -0.113, 1.226));
	return vec3(R,G,B);
}


void main()
{
	vec3 RGB_L = texture2D(l_texture, texCoord).rgb;
	vec3 RGB_R = texture2D(r_texture, texCoord).rgb;
	vec3 RGB = vec3(1,1,1);
	if(anaglyphMode == 0)
		RGB = Anaglyph_Red_Blue(RGB_L, RGB_R);
	else if(anaglyphMode == 1)
		RGB = Anaglyph_Red_Cyan(RGB_L, RGB_R);
	else if(anaglyphMode == 2)
		RGB = Anaglyph_Color(RGB_L, RGB_R);
	else if(anaglyphMode == 3)
		RGB = Anaglyph_HalfColor(RGB_L, RGB_R);
	else if(anaglyphMode == 4)
		RGB = Anaglyph_Optimized(RGB_L, RGB_R);
	else if(anaglyphMode == 5)
		RGB = Anaglyph_Dubois(RGB_L, RGB_R);
	FragColor[0] = vec4(RGB,1);
}