#version 330

uniform sampler2D data;

in vec2 fTexCoord;
out vec4 outColor;

const float inf = 1000000.0;
const int n = 10000;

mat3 sharpenedge = mat3(0, -1, 0,
						-1, 5, -1,
						0, -1, 0);

mat3 normal = mat3(	0, 0, 0,
					0, 1, 0,
					0, 0, 0);

mat3 prewitt = mat3(1, 0, -1,
					1, 0, -1,
					1, 0, -1);

mat3 gauss = mat3(	1, 2, 1,
					2, 4, 2,
					1, 2, 1);

mat3 laplace = mat3(0, 1, 0,
					1, 4, 1,
					0, 1, 0);

vec4 julia (vec2 z, vec2 c)
{
	for(int i = 0; i < n; ++i)
	{
		z = (z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c;

		if(length(z) > inf)
		{
			return vec4(1.0, 1.0, 1.0, 1.0);
		}
	}
	return vec4(0.0, 0.0, 0.0, 1.0);
}

vec4 mandelbrot(vec2 z)
{
	vec2 c = vec2 (-1, 0.1);

	for(int i = 0; i < n; i++)
	{
		z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c;
		if (length(z) > inf) 
		{
			return vec4(1.0, 1.0, 1.0, 1.0);
			//return vec4(log(i/6)); 
		}
	}
	return vec4(0, 0, 0, 1);
}

vec4 simple ()
{
	return texture(data, fTexCoord);
}

float CIELuminancia(vec4 color)
{
	return dot(color.rgb, vec3(0.21, 0.39, 0.4));
}

vec4 grayScale(vec4 color)
{
	float gray = dot(color.rgb, vec3(0.21, 0.39, 0.4));
	return vec4(gray, gray, gray, 1);
}

vec4 filtered(mat3 operator){
	//vec2 coord = fTexCoord * 300;
	vec4 sum = vec4(0);
	for(int i = -1; i <= 1 ; i++)
	{
		for(int j = -1; j <= 1; j++)
		{
			sum+= operator[i+1][j+1] * CIELuminancia(texture(data, (fTexCoord + vec2(i, j)/300)));
		}
	}

	return sum;
}

void main ()
{
	//vec2 z = (fTexCoord - vec2 (0.5, 0.5)) * 10.0;
	//outColor = julia (z, vec2 (-1, 0.1));
	//outColor = simple();
	outColor = mandelbrot(z);
	//outColor = grayScale(simple());
	//outColor = filtered(prewitt);
	//outColor = filtered(sharpenedge);
	//outColor = filtered(gauss/16);
}
