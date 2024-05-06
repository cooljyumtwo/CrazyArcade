#include "Framework.h"

MapEditUI::MapEditUI()
{
	bg = new Quad(L"ResourcesCA/Textures/BG/MapEdit.png");
	bg->Translate(CENTER);

	exitBtn = new Button(L"ResourcesCA/Textures/UI/MapEdit/OkBtn.png", true);
	exitBtn->SetTag("MapEdit_exitBtn");
	exitBtn->Load();
	exitBtn->SetEvent([]() {
		SCENE->ChangeScene("WaitRoom"); 
		});
}

MapEditUI::~MapEditUI()
{
}

void MapEditUI::Update()
{
	bg->UpdateWorld();
	exitBtn->Update();
}

void MapEditUI::PreRender()
{
	
}

void MapEditUI::Render()
{
	bg->Render();
}

void MapEditUI::PostRender()
{
	exitBtn->Render();
}
