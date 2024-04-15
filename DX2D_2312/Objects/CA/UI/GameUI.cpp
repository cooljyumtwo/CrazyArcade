#include "Framework.h"

GameUI::GameUI()
{
	BG = new Quad(L"ResourcesCA/Textures/BG/GameBg.png");
	BG->Translate(CENTER);
}

GameUI::~GameUI()
{
}

void GameUI::Update()
{
	BG->UpdateWorld();
}

void GameUI::PreRender()
{

}

void GameUI::Render()
{
	BG->Render();

}

void GameUI::PostRender()
{
}
