#version 300 es
precision highp float;

out vec4 fragmentColor;
in vec2 tex;

uniform struct {
	sampler2D billboardTexture;
} material;

void main(void) {
	fragmentColor =  //vec4(tex, 0, 1);
	texture( material.billboardTexture, tex );
}
