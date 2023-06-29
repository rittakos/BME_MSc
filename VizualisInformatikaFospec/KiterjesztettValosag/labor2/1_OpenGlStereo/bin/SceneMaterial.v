#version 150 core

uniform vec4 light;
uniform mat4 projection_matrix, view_matrix;
uniform mat4 viewIT_matrix;

in vec4 position;
in vec3 normal;
in vec2 texCoord;
in vec3 tangents;

out vec2 texCoord2;
out vec3 tangents2;
out vec3 lightDir, wNormal, camDir, wPos;

void main()
{
	wPos = position.xyz;
	lightDir = light.xyz - light.w * wPos;
	wNormal = normal;
	texCoord2 = vec2(texCoord.x,1.0-texCoord.y);
	vec3 camPos = (vec4(0,0,0,1) * viewIT_matrix).xyz;
	camDir = camPos - wPos;
	tangents2 = tangents;	
	gl_Position = projection_matrix * view_matrix * position;
}