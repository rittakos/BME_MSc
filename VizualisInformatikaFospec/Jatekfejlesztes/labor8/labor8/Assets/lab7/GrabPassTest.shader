Shader "Custom/GrabPassTest" {
    Properties{
        _Color("Color", Color) = (1,1,1,1)
    }
        SubShader{
            Tags { "Queue" = "Transparent+3" }
            GrabPass{}
            Pass
            {
                Color[_Color]
                SetTexture[_GrabTexture]
                {
                 combine primary * texture
                }
            }
    }
        FallBack "Diffuse"
}

