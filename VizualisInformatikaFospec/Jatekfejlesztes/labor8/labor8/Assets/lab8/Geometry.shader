Shader "Custom/Geometry" {
    Properties{
        _Color("Color", Color) = (1,1,1,1)
        _Emissive("Emissive", Color) = (0,0,0,1)
        _Specular("Specular", Color) = (1,1,1,1)
        _Smoothness("Shininess", Range(0.0, 1.0)) = 0.1
        _Scale("Scale", Range(0.0, 1.0)) = 0.9
        _Width("Width", Range(0.0, 0.01)) = 0.003

    }
    SubShader{
        Tags { "Queue" = "Geometry"}
        Pass
        {
            CGPROGRAM

            #pragma target 4.0

            #pragma vertex mainVS
            #pragma fragment mainPS_red
            #pragma geometry mainGS_border

            #include "Phong.cginc"

            float _Scale;

            [maxvertexcount(3)]
            void mainGS_shrink(triangle VS_OUT IN[3], inout TriangleStream<VS_OUT> stream)
            {
                float4 A = IN[0].hPos;
                float4 B = IN[1].hPos;
                float4 C = IN[2].hPos;

                float T = _Scale;
                IN[0].hPos = lerp(A, lerp(B, C, 0.5), 1 - T);
                IN[1].hPos = lerp(B, lerp(A, C, 0.5), 1 - T);
                IN[2].hPos = lerp(C, lerp(A, B, 0.5), 1 - T);

                stream.Append(IN[0]);
                stream.Append(IN[1]);
                stream.Append(IN[2]);

                stream.RestartStrip();
            }


            [maxvertexcount(3)]
            void mainGS_passthrough(triangle VS_OUT IN[3], inout TriangleStream<VS_OUT> stream)
            {
                stream.Append(IN[0]);
                stream.Append(IN[1]);
                stream.Append(IN[2]);

                stream.RestartStrip();
            }

            float4 mainPS_red(VS_OUT IN) : SV_Target
            {
                return float4(1,0,0,1);
            }


            [maxvertexcount(6)]
            void mainGS_normal(triangle VS_OUT IN[3], inout LineStream<VS_OUT> stream)
            {
                for (int i = 0; i < 3; ++i)
                {
                    float4 wp = float4(IN[i].wPos, 1);
                    wp.xyz = wp.xyz;
                    IN[i].hPos = mul(UNITY_MATRIX_VP, wp);
                    stream.Append(IN[i]);

                    wp.xyz = wp.xyz + IN[i].N * _Scale;
                    IN[i].hPos = mul(UNITY_MATRIX_VP, wp);
                    stream.Append(IN[i]);
                    stream.RestartStrip();
                }
            }

            [maxvertexcount(3)]
            void mainGS_bordertriangles(triangle VS_OUT IN[3], inout TriangleStream<VS_OUT> stream) {
                float dot0 = dot(IN[0].N, IN[0].V);
                float dot1 = dot(IN[1].N, IN[1].V);
                float dot2 = dot(IN[2].N, IN[2].V);

                int found = 0;
                if (dot0 * dot1 < 0) {
                    ++found;
                }
                if (dot0 * dot2 < 0) {
                    ++found;
                }
                if (dot1 * dot2 < 0) {
                    ++found;
                }
                if (found == 0) return;

                stream.Append(IN[0]);
                stream.Append(IN[1]);
                stream.Append(IN[2]);
                stream.RestartStrip();
            }

            float _Width = 1.0f;

            [maxvertexcount(6)]
            void mainGS_border(triangle VS_OUT IN[3], inout TriangleStream<VS_OUT> stream)
            {
                int line1End1 = -1;
                int line1End2 = -1;
                int line2End1 = -1;
                int line2End2 = -1;
                int found = 0;
                float dot0 = dot(IN[0].N, IN[0].V);
                float dot1 = dot(IN[1].N, IN[1].V);
                float dot2 = dot(IN[2].N, IN[2].V);

                if (dot0 * dot1 < 0)
                {
                    line1End1 = 0, line1End2 = 1;
                    ++found;
                }
                if (dot0 * dot2 < 0)
                {
                    if (found == 0) line1End1 = 0, line1End2 = 2;
                    else line2End1 = 0, line2End2 = 2;
                    ++found;
                }
                if (dot1 * dot2 < 0)
                {
                    line2End1 = 1, line2End2 = 2;
                    ++found;
                }

                if (found < 2) return;

                float4 p0, p1;

                float d1 = dot(IN[line1End1].N, IN[line1End1].V);
                float d2 = dot(IN[line1End2].N, IN[line1End2].V);
                p0 = lerp(IN[line1End1].hPos, IN[line1End2].hPos, -d1 / (d2 - d1));
                //p0 = mul(UNITY_MATRIX_VP, float4(lerp(IN[line1End1].wPos, IN[line1End2].wPos, -d1 / (d2 - d1)), 1));

                d1 = dot(IN[line2End1].N, IN[line2End1].V);
                d2 = dot(IN[line2End2].N, IN[line2End2].V);
                p1 = lerp(IN[line2End1].hPos, IN[line2End2].hPos, -d1 / (d2 - d1));
                //p1 = mul(UNITY_MATRIX_VP, float4(lerp(IN[line2End1].wPos, IN[line2End2].wPos, -d1 / (d2 - d1)), 1));

                p0 = p0 / p0.w;
                p1 = p1 / p1.w;
                float2 screenSpaceLineDir = p1.xy - p0.xy;
                float2 screenSpaceExtrudeDir = normalize(float2(screenSpaceLineDir.y, -screenSpaceLineDir.x));

                IN[0].hPos = p0 + float4(screenSpaceExtrudeDir, 0, 0) * _Width;
                stream.Append(IN[0]);
                IN[0].hPos = p1 + float4(screenSpaceExtrudeDir, 0, 0) * _Width;
                stream.Append(IN[0]);
                IN[0].hPos = p0 - float4(screenSpaceExtrudeDir, 0, 0) * _Width;
                stream.Append(IN[0]);
                stream.RestartStrip();

                IN[0].hPos = p1 - float4(screenSpaceExtrudeDir, 0, 0) * _Width;
                stream.Append(IN[0]);
                IN[0].hPos = p0 - float4(screenSpaceExtrudeDir, 0, 0) * _Width;
                stream.Append(IN[0]);
                IN[0].hPos = p1 + float4(screenSpaceExtrudeDir, 0, 0) * _Width;
                stream.Append(IN[0]);
                stream.RestartStrip();
            }

            ENDCG
        }
        /*Pass {
            Tags{ "LightMode" = "ForwardBase" }
            CGPROGRAM

            #pragma target 3.0
            #pragma vertex mainVS
            #pragma fragment mainPS
            #include "Phong.cginc"
            ENDCG
        }*/
    }
    
}