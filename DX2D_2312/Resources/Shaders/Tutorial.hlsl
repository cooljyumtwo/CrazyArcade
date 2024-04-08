//Shader : Shade + er - GPU Program
//Sementic : 매개변수나 반환 자료형이 어떻게 쓰이는지 나타내는 지표
//SV : System Value

float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

float4 PS() : SV_TARGET
{
    return float4(1, 1, 0, 1);
}