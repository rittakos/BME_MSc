#version 150 core

layout(points) in;
layout(points, max_vertices = 9) out;

in vec4 gVelocity[];
in vec4 gLife[];

out vec4 fPosition;
out vec4 fVelocity;
out vec4 fLife;

const float PI = 3.1415f;

void main()
{
	if(gLife[0].x > 0.0)
	{
		fVelocity = gVelocity[0];
		fVelocity.y -= 0.0000002;
		fPosition = gl_in[0].gl_Position + fVelocity;
		if (gLife[0].x <= 0.0) {
			fLife = vec4(1.0,0.0,0.0,0.0);
		} else {
			fLife = gLife[0];
			fLife.x -= 0.0005;
		}

		if(fPosition.y > -0.75f)
		{
			EmitVertex();
			EndPrimitive();
		}
	}

	if (gLife[0].x <= 0.0) {
		for(int idx = 0; idx < 8; ++idx)
		{
			fVelocity = gVelocity[0];
			vec4 dir = vec4(sin(float(idx) * 2.0f*PI/8.0f), cos(float(idx) * 2.0f*PI/8.0f), 0.0f, 1.0f);
			//fVelocity.x = -fVelocity.y;
			fVelocity += normalize(dir) * 0.003f;
			//fVelocity.y = -= 0.0000001f;
			fPosition = gl_in[0].gl_Position + fVelocity;
			fLife = vec4(2.0,0.0,0.0,0.0);

			EmitVertex();
			EndPrimitive();
		}
	} 
}