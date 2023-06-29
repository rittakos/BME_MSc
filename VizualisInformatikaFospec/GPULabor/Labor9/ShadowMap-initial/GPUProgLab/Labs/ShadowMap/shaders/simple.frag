#version 330

in vec4 worldPos;

in vec2 texCoord;
in vec2 shadowCoord;

out vec4 outColor;

uniform mat4 lightViewProjMatrix;
uniform sampler2D modelTexture;
uniform sampler2DShadow depthTexture;

float shadow()
{
    /*vec3 shadowMDC = vec3(lightViewProjMatrix * vec4(worldPos.xyz, 1.0));

    if(abs(shadowMDC.x) < 1.0 && abs(shadowMDC.y) < 1.0 && abs(shadowMDC.z) < 1.0)
    {
        vec2 shadowCoord = vec2(shadowMDC.x * 0.5 + 0.5f, shadowMDC.y * 0.5 + 0.5);
        float shadow = texture(depthTexture, shadowCoord.xy).r;

        if(shadowMDC.z * 0.5 + 0.5 > shadow + 0.01)
            return 0.0;
    }*/

    return 1.0;
}

float shadow2()
{
    vec3 shadowMDC = vec3(lightViewProjMatrix * vec4(worldPos.xyz, 1.0));

    if(abs(shadowMDC.x) < 1.0 && abs(shadowMDC.y) < 1.0 && abs(shadowMDC.z) < 1.0)
    {
       vec2 shadowCoord = vec2(shadowMDC.x * 0.5 + 0.5f, shadowMDC.y * 0.5 + 0.5);
       float bias = 0.03;
       return texture(depthTexture, vec3(shadowCoord.xy, (shadowMDC.z - bias) * 0.5 + 0.5 ));
    }

    return 1.0;
}

void main()
{
    float shadow = shadow2();

	vec4 color = texture(modelTexture, texCoord.xy);

	outColor = color * shadow;
}
