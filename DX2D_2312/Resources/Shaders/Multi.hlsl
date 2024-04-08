//Multi.hlsl
struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer SelectBuffer : register(b1)
{
	int select;
}

cbuffer FloatBuffer : register(b2)
{
	float time;
}

Texture2D map : register(t0);
Texture2D secondMap : register(t1);

SamplerState samp : register(s0);

float4 Modulate(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	
	float2 temp = uv;
	temp.x += time;
	float4 tex2 = secondMap.Sample(samp, temp);

	return tex1 * tex2;
}

float4 Modulate2X(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 * tex2 * 2.0f;
}

float4 Add(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 + tex2;
}

float4 AddSmooth(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 + tex2 - tex1 * tex2;
}

float4 AddSigned(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return tex1 + tex2 - 0.5f;
}

float4 AddSigned2X(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return (tex1 + tex2 - 0.5f) * 2.0f;
}

float4 Subtract(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return float4((tex1 - tex2).rgb, 1.0f);
}

float4 RevSubtract(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);
	float4 tex2 = secondMap.Sample(samp, uv);

	return float4((tex2 - tex1).rgb, 1.0f);
}

float4 Negative(float2 uv)
{
	float4 tex1 = map.Sample(samp, uv);	

	return float4((1.0f - tex1).rgb, 1.0f);
}

float4 PS(Input input) : SV_TARGET
{
	float4 baseColor = map.Sample(samp, input.uv);
 
	if (select == 1)
		return Modulate(input.uv);
	else if (select == 2)
		return Modulate2X(input.uv);
	else if (select == 3)
		return Add(input.uv);
	else if (select == 4)
		return AddSmooth(input.uv);
	else if (select == 5)
		return AddSigned(input.uv);
	else if (select == 6)
		return AddSigned2X(input.uv);
	else if (select == 7)
		return Subtract(input.uv);
	else if (select == 8)
		return RevSubtract(input.uv);
	else if (select == 9)
		return Negative(input.uv);
	
	return baseColor * color;
}