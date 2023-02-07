Shader "Hidden/NewImageEffectShader"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        int levels;
    }
    SubShader
    {
        // No culling or depth
        Cull Off ZWrite Off ZTest Always

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            sampler2D _MainTex;

            float luminance(float3 rgb)
            {
                return 0.2126 * rgb.r + 0.7152 * rgb.g + 0.0722 * rgb.b;
            }

            float4 frag(v2f i) : SV_Target{ // replace the old "frag" with this one
               float3 col = tex2D(_MainTex, i.uv).rgb;
               float luminance_orig = luminance(col);
               int levels = 8;
               float luminance_new = floor(luminance_orig * levels) / levels;
               col.rgb *= luminance_new / luminance_orig;
               return float4(col, 1);
            }



            ENDCG
        }
    }
}
