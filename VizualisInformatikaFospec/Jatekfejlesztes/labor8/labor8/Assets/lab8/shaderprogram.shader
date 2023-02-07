// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'


Shader "Custom/shaderprogram"{
	Properties{
		_Color("Color", Color) = (1,1,1,1)
		_AlbedoMap("Albedo", 2D) = "" {}
		[HDR][NoScaleOffset] _ReflectionMap("_ReflectionMap", CUBE) = "" {}
		[HDR][NoScaleOffset] _DiffuseMap("_DiffuseMap", CUBE) = "" {}

		_Emissive("Emissive", Color) = (0,0,0,1)
		_Specular("Specular", Color) = (1,1,1,1)
		_Smoothness("Smoothness", Range(0,1)) = 0.1
	}
		SubShader{
			Tags{ "Queue" = "Geometry" }

			Pass {
				Tags{ "LightMode" = "ForwardBase" }
				CGPROGRAM

				#pragma target 3.0
				#pragma vertex mainVS
				#pragma fragment mainPS

				
				#include "Phong.cginc"
				ENDCG
			}

			Pass {
				Tags{ "LightMode" = "ForwardAdd" }
				Blend One One
				CGPROGRAM

				#pragma target 3.0
				#pragma vertex mainVS
				#pragma fragment mainPS

				#include "Phong.cginc"
				ENDCG
			}
		}

		FallBack "Diffuse"
}
