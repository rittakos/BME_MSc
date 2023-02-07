Shader "Custom/TestShader2"
{
    Properties{
        _Color("Color", Color) = (1,1,1,1)
        _Ambient("Ambient", Color) = (1,1,1,1)
        _Emissive("Emissive", Color) = (0,0,0,1)
        _Specular("Specular", Color) = (1,1,1,1)
        _Shininess("Shininess", Range(0, 5)) = 0.1
    }
        SubShader{
            Tags { "Queue" = "Transparent" }
            Pass
            {
                colormask 0
            }
            Pass
            {
                ColorMask 0
            }
            Pass
            {
                BlendOp Add
                Blend SrcAlpha OneMinusSrcAlpha
                Lighting On
                SeparateSpecular On
                Material
                {
                    Diffuse[_Color]
                    Ambient[_Color]
                    Emission[_Emissive]
                    Specular[_Specular]
                    Shininess[_Shininess]
                }
            }
    }
        FallBack "Diffuse"
}
