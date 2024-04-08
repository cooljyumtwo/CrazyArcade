#pragma once

class Environment : public Singleton<Environment>
{
private:
	friend class Singleton;

	Environment();
	~Environment();

public:
	void Update();
	void RenderUI();

	void SetAlphaBlend();
	void SetAdditiveBlend();

	void SetViewport(UINT width = SCREEN_WIDTH, UINT height = SCREEN_HEIGHT);
	void SetProjection();

	Camera* GetMainCamera() { return mainCamera; }

private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:	
	Camera* mainCamera;

	MatrixBuffer* projectionBuffer;
	MatrixBuffer* uiViewBuffer;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* alphaBlendState;
	ID3D11BlendState* additiveBlendState;
	ID3D11RasterizerState* rasterizerState;

};