Shader "Custom/ColorCorrectionShader"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        // No culling or depth
        Cull Off ZWrite Off ZTest Always

        Pass
        {
            CGPROGRAM
            #pragma multi_compile __ ATTENUATE_SATURATION
            #pragma multi_compile __ ATTENUATE_BRIGHTNESS
            #pragma vertex vert
            #pragma fragment frag
            //#pragma fragment frag_show_atten

            #include "UnityCG.cginc"
            #include "colorspaces.cginc"

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
            float4 _MainTex_TexelSize;
            float hueShift;
            float saturationScaler;
            float brightnessScaler;
            float attenuationRadius;
            float2 attenuationCenter;

            float4 frag_floating(v2f i) : SV_Target{
                float2 texCoord = i.uv + 0.15 * float2(
                sin(2 * i.uv.x + _Time.y),
                cos(3 * i.uv.y + _Time.z));
                float4 col = tex2D(_MainTex, texCoord);
                return col;
            }

            float attenuation(float2 uv)
            {
                float2 aspectCorrection = float2(1.0, _MainTex_TexelSize.x / _MainTex_TexelSize.y);
                float dist = length((uv - attenuationCenter) * aspectCorrection);
                return smoothstep(0, 1, 1.0 - dist / attenuationRadius);
            }


            float4 frag_show_atten(v2f i) : SV_Target
            {
               float4 col = tex2D(_MainTex, i.uv);
               col.xyz = attenuation(i.uv);
               return col;
            }


            float4 frag(v2f i) : SV_Target
            {
                float2 texCoord = i.uv;
                texCoord = i.uv + 0.15 * float2(sin(2 * i.uv.x + _Time.y),cos(3 * i.uv.y + _Time.z));
                

                float4 col = tex2D(_MainTex, i.uv);
                float3 hsv = rgb_to_hsv(col.xyz); // rgb_to_hsv: colorspaces.cginc 
                hsv.x = frac(hsv.x + hueShift);
                hsv.y *= saturationScaler;
                hsv.z *= brightnessScaler;
            #ifdef ATTENUATE_SATURATION // C# szkript, material.EnableKeyword és DisableKeyword
                hsv.y *= attenuation(i.uv);
            #endif
            #ifdef ATTENUATE_BRIGHTNESS // C# szkript, material.EnableKeyword és DisableKeyword
                hsv.z *= attenuation(i.uv);
            #endif

                col.xyz = hsv_to_rgb(hsv); // hsv_to_rgb: colorspaces.cginc 
                return col;
            }

            ENDCG
        }
    }
}
