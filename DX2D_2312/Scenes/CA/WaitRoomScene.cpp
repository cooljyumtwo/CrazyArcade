#include "Framework.h"
#include "WaitRoomScene.h"

WaitRoomScene::WaitRoomScene()
{
}

WaitRoomScene::~WaitRoomScene()
{
}

void WaitRoomScene::Update()
{
}

void WaitRoomScene::Render()
{
}

void WaitRoomScene::PostRender()
{
}

void WaitRoomScene::Start()
{
	GameManager::isGUI = false;

    if (!Audio::Get()->IsPlaySound("WaitRoomBgm"))
    {
        Audio::Get()->Play("WaitRoomBgm", 0.5f);
    }
}

void WaitRoomScene::End()
{
    Audio::Get()->Stop("WaitRoomBgm");
}
