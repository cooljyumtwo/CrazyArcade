#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    EffectManager::Get()->Add("Slash", 10, L"Resources/Textures/FX/Slash_5x2.png",
        Vector2(5, 2));
    EffectManager::Get()->Add("Hit", 10, L"Resources/Textures/FX/Hit_5x1.png",
        Vector2(5, 1));
    EffectManager::Get()->Add("Fire", 10, L"Resources/Textures/FX/Fire_4x2.png",
        Vector2(4, 2), 1, true);
    EffectManager::Get()->Add("Fire2", 10, L"Resources/Textures/FX/Fire_8x2.png",
        Vector2(8, 2), 1, true);

    cookie = new Cookie();
    cookie->SetLocalPosition(CENTER);

    FloorManager::Get()->Load();

    renderTarget = new RenderTarget();

    Texture* texture = Texture::Add(L"RT", renderTarget->GetSRV());

    Quad* quad = new Quad(Vector2(CENTER_X, CENTER_Y), false);
    quad->GetMaterial()->SetPixelShader(L"Filter.hlsl");
    quad->GetMaterial()->SetTexture(texture);
    quad->SetLocalPosition(CENTER * 0.5f);
    quad->Update();
    renderTextures.push_back(quad);

    quad = new Quad(Vector2(CENTER_X, CENTER_Y), false);    
    quad->GetMaterial()->SetTexture(texture);
    quad->SetLocalPosition(CENTER * 0.5f + CENTER);
    quad->Update();
    renderTextures.push_back(quad);
}

RenderTargetScene::~RenderTargetScene()
{
    FloorManager::Delete();
    EffectManager::Delete();

    delete renderTarget;
}

void RenderTargetScene::Update()
{
}

void RenderTargetScene::PreRender()
{
    renderTarget->Set();

    FloorManager::Get()->Render();
}

void RenderTargetScene::Render()
{
    
}

void RenderTargetScene::PostRender()
{
    for (Quad* renderTexture : renderTextures)
        renderTexture->Render();
}
