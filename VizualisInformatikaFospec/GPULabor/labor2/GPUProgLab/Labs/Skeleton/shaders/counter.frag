#version 420

uniform sampler2D data;

layout(binding = 0, offset = 0) uniform atomic_uint counter;

in vec2 fTexCoord;
out vec4 outColor;

void main()
{
	
	//outColor = texture(data, fTexCoord);
	float color = atomicCounterIncrement(counter) / (600 * 600);
	outColor = vec4(0.0f, color, 0.0f, 1.0f);
}
