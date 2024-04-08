cbuffer WorldBuffer : register(b0)
{
    //matrix world;
    float4x4 world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;    
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct Input
{
    float4 pos : POSITION;    
};

struct Output
{
    float4 pos : SV_POSITION;    
};

Output VS(Input input)
{
    Output output;
    output.pos = mul(input.pos, world);    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);    
    
    return output;
}