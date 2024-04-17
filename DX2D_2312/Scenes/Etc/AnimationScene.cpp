#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    CreateEffects();
    CreateRenderTarget();

    cookie = new Cookie();
    cookie->SetLocalPosition(CENTER);

    FloorManager::Get()->Load();
}

AnimationScene::~AnimationScene()
{
    EffectManager::Delete();

    delete renderTarget;
    delete renderTexture;
    delete lightBuffer;
}

void AnimationScene::Update()
{
    Vector2 pos = cookie->GetLocalPosition();
    pos.y = SCREEN_HEIGHT - (pos.y - 100);

    lightBuffer->GetData().lightPos = pos;

    cookie->Update();
}

void AnimationScene::PreRender()
{
    renderTarget->Set();

    FloorManager::Get()->Render();
    cookie->Render();
}

void AnimationScene::Render()
{
    
}

void AnimationScene::PostRender()
{
    lightBuffer->SetPS(1);
    renderTexture->Render();

    cookie->PostRender();
}

void AnimationScene::CreateEffects()
{
    EffectManager::Get()->Add("Slash", 10, L"Resources/Textures/FX/Slash_5x2.png",
        Vector2(5, 2));
    EffectManager::Get()->Add("Hit", 10, L"Resources/Textures/FX/Hit_5x1.png",
        Vector2(5, 1));
    EffectManager::Get()->Add("Fire", 10, L"Resources/Textures/FX/Fire_4x2.png",
        Vector2(4, 2), 1, true);
    EffectManager::Get()->Add("Fire2", 10, L"Resources/Textures/FX/Fire_8x2.png",
        Vector2(8, 2), 1, true);
}

void AnimationScene::CreateRenderTarget()
{
    renderTarget = new RenderTarget();

    Texture* texture = Texture::Add(L"RT", renderTarget->GetSRV());

    renderTexture = new Quad(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT), false);
    renderTexture->GetMaterial()->SetPixelShader(L"Light.hlsl");
    renderTexture->GetMaterial()->SetTexture(texture);
    renderTexture->SetLocalPosition(CENTER);
    renderTexture->Update();

    lightBuffer = new LightBuffer();

    lightBuffer->GetData().imageSize = renderTexture->GetSize();
    lightBuffer->GetData().range = 300.0f;
    lightBuffer->GetData().attenuation = 1.5f;
}
