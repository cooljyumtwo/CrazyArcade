struct Input
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(Input input) : SV_TARGET
{
    float4 baseColor = map.Sample(samp, input.uv);
    
    return baseColor * color;
}