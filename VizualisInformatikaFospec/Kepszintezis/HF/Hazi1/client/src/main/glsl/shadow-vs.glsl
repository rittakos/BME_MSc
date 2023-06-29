#version 300 es

in vec4 vertexPosition;

uniform mat4 depthMVP;

void main(){
 gl_Position =  depthMVP * vertexPosition;
}