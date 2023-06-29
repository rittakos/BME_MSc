#version 300 es 
precision highp float;

out vec4 fragmentColor;
in vec4 texCoord;
in vec4 worldNormal;
in vec4 worldPosition;
in vec4 debugColor;

uniform struct{
	sampler2D colorTexture;
} material;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;

uniform struct {
  vec4 position;
  vec3 powerDensity;
} lights[8];

vec3 shade(
  vec3 normal, vec3 lightDir,
  vec3 powerDensity, vec3 materialColor) {

  float cosa =
    clamp( dot(lightDir, normal), 0.0, 1.0);
  return
    powerDensity * materialColor * cosa;
}

void main(void) {
  //fragmentColor = debugColor;
  //return;

  vec3 normal = normalize(worldNormal.xyz);

  vec3 x = worldPosition.xyz / worldPosition.w;
  vec3 viewDir = normalize(camera.position - x);

  fragmentColor = vec4(0, 0, 0, 1);
  for(int i=0; i<1; i++){
    vec3 lightDir = lights[i].position.xyz;
    vec3 powerDensity = lights[i].powerDensity;

    fragmentColor.rgb += shade(normal, lightDir, 
      powerDensity,
      texture(material.colorTexture, texCoord.xy/texCoord.w).rgb);
  }

}
