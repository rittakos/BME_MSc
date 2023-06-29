Shader "Custom/Water"
{
    Properties{
         _Color("Color", Color) = (1,1,1,1)
         _Ambient("Ambient", Color) = (1,1,1,1)
         _Emissive("Emissive", Color) = (0,0,0,1)
         _Specular("Specular", Color) = (1,1,1,1)
         _Shininess("Shininess", Range(0, 5)) = 0.1
    }
    SubShader
    {
        Pass
        {
            Tags{"Queue" = "Geometry"}
            Lighting On
            Material
            {
                Diffuse[_Color]
                Ambient[_Color]
            }
            Stencil{
                Ref 1
                Comp Equal
            }
        }
    }
        FallBack "Diffuse"
}
