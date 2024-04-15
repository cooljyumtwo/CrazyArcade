#include "Framework.h"

MapEditUI::MapEditUI()
{
	BG = new Quad(L"ResourcesCA/Textures/BG/MapEdit.png");
	BG->Translate(CENTER);
}

MapEditUI::~MapEditUI()
{
}

void MapEditUI::Update()
{
	BG->UpdateWorld();
}

void MapEditUI::PreRender()
{
	
}

void MapEditUI::Render()
{
	BG->Render();
}

void MapEditUI::PostRender()
{
}
