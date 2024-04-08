struct Input
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

cbuffer LightBuffer : register(b1)
{
	float2 imageSize;
	float2 lightPos;
	
	float range;
	float attenuation;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 CircleLight(float2 uv)
{
	float4 baseColor = map.Sample(samp, uv);
	
	float2 pixelCoord = imageSize * uv;
	
	float dist = distance(lightPos, pixelCoord);
	
	float temp = 1.0f - saturate(dist / range);
	
	temp = pow(temp, attenuation);
	
	return float4((baseColor * temp).rgb, baseColor.a);
}

float4 PS(Input input) : SV_TARGET
{
	//float4 baseColor = map.Sample(samp, input.uv);    	
	
	return CircleLight(input.uv) * color;
}