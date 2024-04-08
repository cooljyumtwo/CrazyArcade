#pragma once

class Material
{
public:
	Material();
	Material(wstring textureFile, wstring shaderFile = L"PixelUV.hlsl");
	
	void Set();

	void SetTexture(wstring file);
	void SetTexture(Texture* texture) { this->texture = texture; }

	void SetVertexShader(wstring file);
	void SetPixelShader(wstring file);

	Texture* GetTexture() { return texture; }
	ColorBuffer* GetColor() { return colorBuffer; }

	void SetColor(float r, float g, float b, float a = 1.0f)
	{
		colorBuffer->SetColor(r, g, b, a);
	}

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	ColorBuffer* colorBuffer;

	Texture* texture = nullptr;
};