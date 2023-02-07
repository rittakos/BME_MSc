Shader "Custom/Glass"
{
    Properties{
        _Color("Color", Color) = (1,1,1,1)
        _Ambient("Ambient", Color) = (1,1,1,1)
        _Emissive("Emissive", Color) = (0,0,0,1)
        _Specular("Specular", Color) = (1,1,1,1)
        _Shininess("Shininess", Range(0, 5)) = 0.1
    }
        SubShader{
            Tags{"Queue" = "Geometry-1"}
            Pass
            {
                Cull Off
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
                Stencil
                {
                    Ref 1
                    Pass Replace
                }
            }
    }
        FallBack "Diffuse"
}
