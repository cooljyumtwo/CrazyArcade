#include "Framework.h"
#include "PixelShaderScene.h"

PixelShaderScene::PixelShaderScene()
{
    //quad = new Quad(L"Resources/Textures/BG/Test3.jpg", false);
    quad = new Quad(L"Resources/Textures/BG/bg.png", false);
    quad->SetLocalPosition(CENTER);
    quad->Update();
    //quad->GetMaterial()->SetPixelShader(L"Filter.hlsl");
    //quad->GetMaterial()->SetPixelShader(L"Outline.hlsl");
    //quad->GetMaterial()->SetPixelShader(L"Multi.hlsl");
    quad->GetMaterial()->SetPixelShader(L"Light.hlsl");

    valueBuffer = new IntValueBuffer();
    valueBuffer->Get()[0] = 100;
    valueBuffer->Get()[2] = quad->GetSize().x;
    valueBuffer->Get()[3] = quad->GetSize().y;

    outlineBuffer = new FloatValueBuffer();
    outlineBuffer->Get()[0] = quad->GetSize().x;
    outlineBuffer->Get()[1] = quad->GetSize().y;
    outlineBuffer->Get()[2] = quad->GetSize().x * 0.5f;
    outlineBuffer->Get()[3] = quad->GetSize().y * 0.5f;

    outlineColorBuffer = new ColorBuffer();

    secondMap = Texture::Add(L"Resources/Textures/BG/rainbow.png");
    //secondMap = Texture::Add(L"Resources/Textures/BG/sun.png");
}

PixelShaderScene::~PixelShaderScene()
{    
    delete quad;
    delete valueBuffer;
    delete outlineBuffer;
    delete outlineColorBuffer;
}

void PixelShaderScene::Update()
{
}

void PixelShaderScene::Render()
{
    outlineBuffer->Get()[0] += DELTA;

    valueBuffer->SetPS(1);
    outlineBuffer->SetPS(2);
    //outlineColorBuffer->SetPS(2);

    secondMap->PSSet(1);
    quad->Render();
}

void PixelShaderScene::PostRender()
{
    ImGui::DragInt("Select", &valueBuffer->Get()[0]);
    ImGui::DragInt("Scale", &valueBuffer->Get()[1]);
    ImGui::DragFloat("PosX", &outlineBuffer->Get()[2]);
    ImGui::DragFloat("PosY", &outlineBuffer->Get()[3]);
    Float4 color = outlineColorBuffer->GetColor();
    ImGui::ColorEdit4("OutlineColor", (float*)&color);
    outlineColorBuffer->SetColor(color);
}
