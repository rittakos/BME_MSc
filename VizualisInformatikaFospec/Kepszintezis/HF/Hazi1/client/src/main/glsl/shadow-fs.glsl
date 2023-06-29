#version 300 es
precision highp float;

out vec4 fragmentDepth;

void main(){
    fragmentDepth = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z);
}