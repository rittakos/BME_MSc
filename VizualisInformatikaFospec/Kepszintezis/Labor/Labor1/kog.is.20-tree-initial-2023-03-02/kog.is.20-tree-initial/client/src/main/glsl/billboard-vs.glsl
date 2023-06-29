#version 300 es
in vec4 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 billboardPosition;

in vec4 billboardNormal;
out vec2 tex; // passed to FS

uniform struct {
	mat4 modelMatrix;
  mat4 modelMatrixInverse;
} gameObject;

uniform struct {
  mat4 viewProjMatrix;
	vec2 billboardSize;
} camera;

void main(void) {

	vec4 p = billboardPosition;
	p.xy += vertexPosition.xy * 0.1;

	gl_Position = p
    * gameObject.modelMatrix * camera.viewProjMatrix;

	tex = vertexTexCoord;
}
