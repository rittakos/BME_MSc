#version 300 es 
precision highp float;

in vec2 texCoord;
out vec4 fragmentColor;

uniform struct {
	sampler2D averagedFrame;
} mesh;

void main(void) {
	fragmentColor = 
		texture(mesh.averagedFrame, texCoord);
}
