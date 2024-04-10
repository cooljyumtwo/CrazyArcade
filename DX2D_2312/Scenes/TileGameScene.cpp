#include "Framework.h"
#include "TileGameScene.h"

TileGameScene::TileGameScene()
{
    CAM->SetFix(false);

    //tileMap = new GameTileMap("Resources/TextData/Map/Test.map");

    amazon = new Amazon();
    amazon->SetLocalPosition(CENTER);
}

TileGameScene::~TileGameScene()
{
   // delete tileMap;
    delete amazon;
}

void TileGameScene::Update()
{
    amazon->Update();
}

void TileGameScene::Render()
{
  //  tileMap->Render();
    amazon->Render();
}

void TileGameScene::PostRender()
{
}
