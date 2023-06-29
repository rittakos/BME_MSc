#version 330 core
in vec4 gl_FragCoord;
 
out vec4 fragColor;
 
uniform vec2 center;
uniform float zoom;
 
const int maxIterations = 600;
const float inf = 1000000000.0f;

 
int mandelbrot()
{
	vec2 z = vec2(((gl_FragCoord.x / 600.0f - 0.5f) * zoom + center.x), ((gl_FragCoord.y / 600.0f - 0.5f) * zoom + center.y));
 
    int iterations = 0;
	
	vec2 c = vec2 (-1, 0.1);
 
    while (iterations < maxIterations)
    {
		z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y) + c;
		
		if (length(z) > inf) 
			return iterations;
 
        ++iterations;
    }
    return iterations;
}
 
 
vec4 return_color()
{
    int iter = mandelbrot();
	
    if (iter == maxIterations)
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
 
	if (iter < 15.0f)
		return vec4(0.0f, 0.0f, log(float(iter)/8), 1.0f);
    else if (iter < 30.0f)
		return vec4(0.0f, log(float(iter)/8), 0.0f, 1.0f);
    else
		return vec4(log(float(iter)/8), 0.0f, 0.0f, 1.0f);
}
 
void main()
{
    fragColor = return_color();
}