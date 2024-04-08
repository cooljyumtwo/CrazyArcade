struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer ValueBuffer : register(b1)
{
	float fillAmount;
}

Texture2D frontMap : register(t0);
Texture2D backMap : register(t1);

SamplerState samp : register(s0);

float4 PS(Input input) : SV_TARGET
{
	float4 baseColor;
	
	if (input.uv.x < fillAmount)
		baseColor = frontMap.Sample(samp, input.uv);
	else
		baseColor = backMap.Sample(samp, input.uv);
    
	return baseColor * color;
}