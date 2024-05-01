#include "Framework.h"

GameUI::GameUI()
{
	bg = new Quad(L"ResourcesCA/Textures/BG/GameBg.png");
	bg->Translate(CENTER);

	gameTxt = new Quad(L"ResourcesCA/Textures/UI/Game/GameStart.png");
	gameTxt->SetTag("Game_GameTxt");
	gameTxt->Load();
	gameTxt->SetActive(false);

	bossReadyTxt = new Quad(L"ResourcesCA/Textures/UI/Game/Ready.png");
	bossReadyTxt->SetTag("Game_BossReadyTxt");
	bossReadyTxt->Load();
	bossReadyTxt->SetActive(true);

	resultWindow = new Quad(L"ResourcesCA/Textures/UI/Game/ResultWindow.png");
	resultWindow->SetTag("Game_ResultWindow");
	resultWindow->Load();
	resultWindow->SetActive(false);
	
	wstring str = L"ResourcesCA/Textures/Item/BubbleNeedle.png"; 
	itemSlotImg = new Quad(Vector2{40, 40});
	itemSlotImg->SetTag("Game_ItemSlotImg");
	itemSlotImg->Load();
	itemSlotImg->SetActive(false);

	//gameTxtTexs
	gameTxtTexs.resize(gameTxtStrs.size());

	FOR(gameTxtStrs.size())
		gameTxtTexs[i] = Texture::Add(PATH_GAME + gameTxtStrs[i]);
}

GameUI::~GameUI()
{
	delete bg;
	delete gameTxt;
}

void GameUI::Update()
{
	bg->UpdateWorld();
	gameTxt->UpdateWorld();
	bossReadyTxt->UpdateWorld();
	resultWindow->UpdateWorld();
	itemSlotImg->UpdateWorld();

	AniBossTxt();
	AniGameTxt();
}

void GameUI::PreRender()
{
}

void GameUI::Render()
{
	bg->Render();

	itemSlotImg->RenderUI();
}

void GameUI::PostRender()
{
	bossReadyTxt->Render();
	gameTxt->Render();
	resultWindow->Render();
	itemSlotImg->Render();
}

void GameUI::SetGameTxt(State state)
{
	if (curState == GAMEOVER) return;

	curState = state;
	gameTxt->GetMaterial()->SetTexture(gameTxtTexs[(int)curState]);
	count = 0;
}

void GameUI::AniGameTxt()
{
	if (curState == START)
	{
		if (count > MAX_COUNT) 
			return;
	}
	else 
	{
		if (count > MAX_COUNT * 2) 
		{
			resultWindow->SetActive(false);
			if (curState == GAMEOVER)
				StageManager::Get()->End();
			else
				StageManager::Get()->NextStage();

			return;
		}
	}
		
	frameTime += DELTA;

	if (frameTime > MAX_FRAME_TIME)
	{
		frameTime -= MAX_FRAME_TIME;
		
		if(count <= MAX_COUNT)
			gameTxt->SetActive(!gameTxt->IsActive());
		else
		{
			resultWindow->SetActive(true);
		}

		count++;
	}	
}

void GameUI::AniBossTxt()
{
	if (!bossReadyTxt->IsActive()) return;

	if (bossReadyTxt->GetGlobalPosition().x + bossReadyTxt->GetSize().x < 0)
		bossReadyTxt->SetActive(false);

	if (count >= 2)
		bossReadyTxt->Translate(Vector2::Left() * 10.0f);
}

void GameUI::SetItemSlotImg(bool isItem, wstring imgStr)
{
	itemSlotImg->SetActive(isItem);
	
	if(isItem)
		itemSlotImg->GetMaterial()->SetTexture(Texture::Add(imgStr));
}

void GameUI::End()
{
	count = MAX_COUNT;
	curState = START;
	bossReadyTxt->Load();
}


