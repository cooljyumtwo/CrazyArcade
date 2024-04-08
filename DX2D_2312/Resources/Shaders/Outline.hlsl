struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer OutlineBuffer : register(b1)
{
	float4 outlineColor;
	
	float2 imageSize;
	float weight;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(Input input) : SV_TARGET
{
	float4 baseColor = map.Sample(samp, input.uv);
	
	if (baseColor.a > 0.0f)
		return baseColor * color;
	
	float count = 0;
	
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			float2 offset = (float2(x, y) / imageSize) * weight;
			count += map.Sample(samp, input.uv + offset).a;
		}
	}
	
	if (count > 0 && count < 9)
		return outlineColor;
    
	return baseColor * color;
}