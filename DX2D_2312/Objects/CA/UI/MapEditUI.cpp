#include "Framework.h"

MapEditUI::MapEditUI()
{
	BG = new Quad(L"ResourcesCA/Textures/BG/MapEdit.png");
	BG->Translate(CENTER);

	exitBtn = new Button(L"ResourcesCA/Textures/UI/Button_StartBtn.png");
	exitBtn->Translate(CENTER);
	exitBtn->Load();
	exitBtn->SetEvent([]() {
		SCENE->ChangeScene("Game"); 
		});

}

MapEditUI::~MapEditUI()
{
}

void MapEditUI::Update()
{
	BG->UpdateWorld();
	exitBtn->Update();
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
	exitBtn->Render();
}
