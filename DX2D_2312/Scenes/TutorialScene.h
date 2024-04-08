#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();
		
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ColorBuffer* colorBuffer;

	MatrixBuffer* worldBuffer;	

	XMFLOAT4X4 worldMatrix;

	//float value = 1.0f;

	Vector2 pos;
	Vector2 scale = { 1, 1 };
	float angle = 0.0f;

	vector<VertexColor> vertices;
	vector<UINT> indices;
};