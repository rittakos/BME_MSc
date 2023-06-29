#version 300 es 
precision highp float;

out vec4 fragmentColor;
in vec4 rayDir;
in vec4 vertexToLight;

uniform struct {
	samplerCube envTexture;
} material;

bool inShadow()
{
  vec3 v = vertexToLight.xyz / vertexToLight.w;
  v = v * 0.5 + 0.5;
  vec4 color = texture(material.envTexture, v.xyz);
  float d = color.r;
  if ( v.z <= d)
    return false;
  return true;
}

void main(void) {
  fragmentColor = texture(material.envTexture, rayDir.xyz);
  if(inShadow())
    fragmentColor.w = 0.5;
}
