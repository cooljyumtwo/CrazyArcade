#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
    //FOR(SIZE)
    //{
    //    Quad* quad = new Quad(L"Resources/Textures/Tiles/voxelTile_01.png");
    //    float x = Random(0, SCREEN_WIDTH);
    //    float y = Random(0, SCREEN_HEIGHT);
    //    quad->SetLocalPosition(x, y);
    //
    //    x = Random(0.1f, 1.0f);
    //    y = Random(0.1f, 1.0f);
    //
    //    quad->SetLocalScale(x, y);        
    //}

    quad = new Quad(L"Resources/Textures/Tiles/voxelTile_01.png", false);
    quad->GetMaterial()->SetVertexShader(L"VertexInstancing.hlsl");

    instances.resize(SIZE);

    for (Matrix& instance : instances)
    {
        Transform transform;
        float x = Random(0, SCREEN_WIDTH);
        float y = Random(0, SCREEN_HEIGHT);
        transform.SetLocalPosition(x, y);
        
        x = Random(0.1f, 1.0f);
        y = Random(0.1f, 1.0f);
        
        transform.SetLocalScale(x, y);
        transform.UpdateWorld();

        instance = XMMatrixTranspose(transform.GetWorld());
    }

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), SIZE);
}

InstancingScene::~InstancingScene()
{
    delete quad;
    delete instanceBuffer;
}

void InstancingScene::Update()
{
}

void InstancingScene::Render()
{
    instanceBuffer->Set(1);

    quad->SetRender();

    DC->DrawIndexedInstanced(6, SIZE, 0, 0, 0);
}

void InstancingScene::PostRender()
{
}
