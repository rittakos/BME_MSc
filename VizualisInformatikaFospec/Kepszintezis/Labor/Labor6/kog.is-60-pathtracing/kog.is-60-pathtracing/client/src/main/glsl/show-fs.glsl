#version 300 es 
precision highp float;

in vec2 tex;
out vec4 fragmentColor;

uniform struct {
	sampler2D averagedFrame;
} program;

void main(void) {
	fragmentColor = 
		texture(program.averagedFrame, tex);
}
