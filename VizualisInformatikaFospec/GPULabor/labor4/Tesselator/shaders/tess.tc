#version 430

layout(vertices = 3) out;

in vec3 tPosition[];
out vec3 tcPosition[];

uniform int tessLevelInner;
uniform int tessLevelOuter;

void main()
{
	tcPosition[gl_InvocationID] = tPosition[gl_InvocationID];
	if(gl_InvocationID == 0)
	{
		gl_TessLevelInner[0] = tessLevelInner;

		gl_TessLevelOuter[0] = tessLevelOuter;
		gl_TessLevelOuter[1] = tessLevelOuter + 1;
		gl_TessLevelOuter[2] = tessLevelOuter + 2;
	}
}