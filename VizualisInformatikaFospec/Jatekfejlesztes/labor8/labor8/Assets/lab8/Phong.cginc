float4 _Color;
fixed4 _LightColor0;
float _Smoothness;
fixed4 _Specular;
uniform samplerCUBE _ReflectionMap;
uniform samplerCUBE _DiffuseMap;

struct VS_OUT
{
	float4 hPos : SV_Position;
	float3 N : NORMAL;
	float2 texCoord : TEXCOORD0;
	float3 L : TEXCOORD1;
	float3 V : TEXCOORD2;
	float3 wPos : TEXCOORD3;
};


VS_OUT mainVS(float4 position : POSITION,
	float3 normal : NORMAL
)
{
	VS_OUT OUT = (VS_OUT)0;
	OUT.hPos = UnityObjectToClipPos(position); // = mul MVP
	float3 wPos = mul(unity_ObjectToWorld, position).xyz;
	float3 wNormal = mul(float4(normal, 0), unity_WorldToObject).xyz;
	OUT.N = normalize(wNormal);
	OUT.L = normalize(_WorldSpaceLightPos0.xyz - wPos * _WorldSpaceLightPos0.w);
	OUT.V = normalize(_WorldSpaceCameraPos.xyz - wPos);
	OUT.wPos = wPos;
	return OUT;
}

float4 mainPS(VS_OUT IN) : SV_Target
{
	float3 N = normalize(IN.N);
	float3 L = normalize(IN.L);
	float3 V = normalize(IN.V);

	float NdL = max(0, dot(L, N));
	float3 H = normalize(L + V);
	float specularPower = pow(2048.0, _Smoothness);

	float3 albedo = _Color;
	float diffuse = 1.0; //Lambert
	float specular = pow(max(0, dot(N, H)), specularPower); //Phong-Blinn
	float3 F = _Specular + (float3(1, 1, 1) - _Specular) * pow(1.0 - dot(L, H), 5); //Fresnel
	float3 finalColor = _LightColor0 * lerp(albedo * diffuse, specular, F) * NdL;
#ifdef AMBIENT_LIGHT
	float3 FI = _Specular + (float3(1, 1, 1) - _Specular) * pow(1.0 - dot(V, N), 5); //Fresnel
	float3 R = reflect(-V, N);
	float4 reflection = texCUBElod(_ReflectionMap, float4(R, (1 - _Smoothness) * 6));
	finalColor += lerp(albedo * texCUBE(_DiffuseMap, N), reflection, FI);
#endif
	return float4(finalColor, 1);


}