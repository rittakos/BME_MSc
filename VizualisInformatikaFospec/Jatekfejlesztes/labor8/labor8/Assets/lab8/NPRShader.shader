Shader "Custom/NPRShader" {
	Properties{
			[NoScaleOffset] _ColorMap("Color", 2D) = "" {}
			_ContourSize("Contour Size", Range(0,1)) = 0.1
	}
		SubShader{
			Tags { "Queue" = "Geometry"}
			Pass
			{
				Tags{ "LightMode" = "ForwardBase" }
				CGPROGRAM
				#pragma target 3.0
				#pragma vertex mainVS
				#pragma fragment mainPS

				uniform sampler2D _ColorMap;
				float _ContourSize;

				struct VS_OUT
				{
					float4 hPos : SV_Position;
					float3 N : NORMAL;
					float3 L : TEXCOORD1;
					float3 V : TEXCOORD2;
				};
				VS_OUT mainVS(float4 position : POSITION,
					float3 normal : NORMAL,
					float2 texCoord : TEXCOORD
				)
				{
					VS_OUT OUT = (VS_OUT)0;
					OUT.hPos = UnityObjectToClipPos(position);
					float3 wPos = mul(unity_ObjectToWorld, position).xyz;
					float3 wNormal = mul(float4(normal, 0), unity_WorldToObject).xyz;
					OUT.N = normalize(wNormal);
					OUT.L = normalize(_WorldSpaceLightPos0.xyz - wPos * _WorldSpaceLightPos0.w);
					OUT.V = normalize(_WorldSpaceCameraPos.xyz - wPos);
					return OUT;
				}

				float4 mainPS(VS_OUT IN) : SV_Target
				{
					float3 N = normalize(IN.N);
					float3 L = normalize(IN.L);
					float3 V = normalize(IN.V);

					float NdL = max(0,dot(L, N));
					float3 albedo = tex2D(_ColorMap, float2(NdL, 0.5));
					float contour = dot(N, V) > _ContourSize;
					contour *= contour;
					float3 finalColor = albedo * contour;
					return float4(finalColor, 1);
				}

					ENDCG
			}
		}
}