#include "Framework.h"

GameUI::GameUI()
{
	BG = new Quad(L"ResourcesCA/Textures/BG/GameBg.png");
	BG->Translate(CENTER);

	GameTxt = new Quad(L"ResourcesCA/Textures/UI/Game/GameOver.png");
	GameTxt->SetTag("Game_GameTxt");
	GameTxt->Load();

	//gameTxtTexs
	gameTxtTexs.resize(gameTxtStrs.size());

	FOR(gameTxtStrs.size())
		gameTxtTexs[i] = Texture::Add(PATH_GAME + gameTxtStrs[i]);

}

GameUI::~GameUI()
{
	delete BG;
	delete GameTxt;
}

void GameUI::Update()
{
	BG->UpdateWorld();
	GameTxt->UpdateWorld();

	if (frameTime<5.0f)
	{
		frameTime += DELTA;
		GameTxt->SetActive(!GameTxt->IsActive());
	}
	else { GameTxt->SetActive(false); }
}

void GameUI::PreRender()
{
}

void GameUI::Render()
{
	BG->Render();
	GameTxt->Render();
	GameTxt->RenderUI();

}

void GameUI::PostRender()
{
	GameTxt->Render();
}

void GameUI::SetGameTxt(State state)
{
	GameTxt->GetMaterial()->SetTexture(gameTxtTexs[(int)state]);
}
