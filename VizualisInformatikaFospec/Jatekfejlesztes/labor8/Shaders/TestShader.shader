// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/TestShader"{
	Properties{
		_Color("Color", Color) = (1,1,1,1)
		_Emissive("Emissive", Color) = (0,0,0,1)
		_Specular("Specular", Color) = (1,1,1,1)
		_Smoothness("Smoothness", Range(0,1)) = 0.1
		 [HDR][NoScaleOffset] _ReflectionMap("_ReflectionMap", CUBE) = "" {}
		 [HDR][NoScaleOffset] _DiffuseMap("_DiffuseMap", CUBE) = "" {}
	}
		SubShader{
			Tags{ "Queue" = "Geometry" }

			Pass {
				Tags{ "LightMode" = "ForwardBase" }
				CGPROGRAM

				#pragma target 3.0
				#pragma vertex mainVS
				#pragma fragment mainPS

				#define AMBIENT_LIGHT
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
