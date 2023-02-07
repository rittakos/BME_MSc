#version 150 core

uniform sampler2D color_texture;
uniform sampler2D normal_texture;
uniform vec3 surfaceColor;

in vec3 lightDir, wNormal, camDir, wPos;
in vec2 texCoord2;
in vec3 tangents2;
out vec4 FragColor[1];


void main()
{
	vec3 N = normalize(wNormal);
	vec3 V = normalize(camDir);
	vec3 L = normalize(vec3(0.1,0.5,0.5));
	if(length(tangents2) > 0.001)
	{
		vec3 T = normalize(tangents2);
		vec3 B = cross(T,N);
		mat3 T2W = mat3(T,B,N);

		vec3 tangentN = texture(normal_texture, texCoord2).rgb;
		tangentN.xyz = (tangentN.xyz - vec3(0.5,0.5,0.5)) * 2.0;
		N = T2W * tangentN;
	}
		
	float NdotL = dot(N,L)*0.5+0.5;
	
	vec3 diffuseColor = NdotL*surfaceColor * texture(color_texture, texCoord2).rgb;
	vec4 finalColor = vec4(diffuseColor,1);
	//finalColor = vec4(N,1);
	
	FragColor[0] = finalColor;
}