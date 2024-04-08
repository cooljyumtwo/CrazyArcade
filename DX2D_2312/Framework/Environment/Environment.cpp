#include "Framework.h"

Environment::Environment()
{
	mainCamera = new Camera();
	uiViewBuffer = new MatrixBuffer();

	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();
}

Environment::~Environment()
{
	delete mainCamera;
	delete projectionBuffer;
	delete uiViewBuffer;

	samplerState->Release();
	alphaBlendState->Release();
}

void Environment::Update()
{	
	mainCamera->Update();
}

void Environment::RenderUI()
{
	uiViewBuffer->SetVS(1);

	mainCamera->RenderUI();
}

void Environment::SetAlphaBlend()
{
	float blendFactor[4] = {};
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}

void Environment::SetAdditiveBlend()
{
	float blendFactor[4] = {};
	DC->OMSetBlendState(additiveBlendState, blendFactor, 0xffffffff);
}

void Environment::SetViewport(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewport);
}

void Environment::SetProjection()
{
	projectionBuffer->SetVS(2);
}

void Environment::CreateProjection()
{
	projectionBuffer = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH,
		0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);

	projectionBuffer->Set(orthographic);	
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;		
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;	
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	//LOD(Level Of Detail) : 카메라와의 거리에 따라서 퀄리티를 나누는 기술

	DEVICE->CreateSamplerState(&desc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &alphaBlendState);

	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	DEVICE->CreateBlendState(&desc, &additiveBlendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}

void Environment::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

	DC->RSSetState(rasterizerState);
}
