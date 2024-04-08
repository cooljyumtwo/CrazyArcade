#include "Framework.h"
#include "TileGameScene.h"

TileGameScene::TileGameScene()
{
    amazon = new Amazon();
    amazon->SetLocalPosition(CENTER);
}

TileGameScene::~TileGameScene()
{
}

void TileGameScene::Update()
{
}

void TileGameScene::Render()
{
}

void TileGameScene::PostRender()
{
}
