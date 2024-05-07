#include "Framework.h"

GameUI::GameUI()
{
	bg = new Quad(L"ResourcesCA/Textures/UI/Game/GameBg.png");
	bg->Translate(CENTER);
	bg->UpdateWorld();

	RenderManager::Get()->Add("BG", bg);

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

	exitBtn = new Button(L"ResourcesCA/Textures/UI/Game/ExitBtn.png", true);
	exitBtn->SetTag("Game_exitBtn");
	exitBtn->Load();
	exitBtn->SetEvent([]() {
		SCENE->ChangeScene("WaitRoom");
		});

	resultKillMonsterFont = new ImageFont(L"ResourcesCA/Textures/UI/ResultNumber/");
	resultKillMonsterFont->SetParent(resultWindow);
	resultKillMonsterFont->SetLocalPosition(resultWindow->GetLocalPosition());
	resultKillMonsterFont->Translate({ 58.0f, -33.0f });
	resultKillMonsterFont->UpdateWorld();
	resultKillMonsterFont->SetAligned(ImageFont::AlignedType::R);

	stateFont.resize(4);
	FOR(4)
	{
		stateFont[i] = new ImageFont(L"ResourcesCA/Textures/UI/ResultNumber/");

		stateFont[i]->SetLocalPosition(666.0f,550.0f);
		stateFont[i]->Translate({ 40.0f*i, 0.0f });
		stateFont[i]->UpdateWorld();
		stateFont[i]->SetAligned(ImageFont::AlignedType::R);
		SetStateFont(i, 0);
	}
}

GameUI::~GameUI()
{
	delete bg;
	delete gameTxt;
	delete exitBtn;
}

void GameUI::Update()
{
	bg->UpdateWorld();
	gameTxt->UpdateWorld();
	bossReadyTxt->UpdateWorld();
	resultWindow->UpdateWorld();
	itemSlotImg->UpdateWorld();
	exitBtn->Update();

	FOR(4)
	{
		stateFont[i]->UpdateWorld();
	}

	AniBossTxt();
	AniGameTxt();
}

void GameUI::PreRender()
{
}

void GameUI::Render()
{
}

void GameUI::PostRender()
{
	bossReadyTxt->Render();
	gameTxt->Render();
	resultWindow->Render();
	itemSlotImg->Render();
	exitBtn->Render();

	resultKillMonsterFont->Render();	


	FOR(4)
	{
		stateFont[i]->Render();
	}
}

void GameUI::SetGameTxt(State state)
{
	curState = state;
	gameTxt->GetMaterial()->SetTexture(gameTxtTexs[(int)curState]);
	count = 0;
	gameTxt->SetActive(false);

	if (MonsterManager::Get()->GetIsSpawnBoss())
	{
		bossReadyTxt->SetActive(true);
	}
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
			resultKillMonsterFont->SetValue((UINT)StageManager::Get()->GetScore());
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

void GameUI::SetStateFont(int idx, int num)
{
	stateFont[idx]->SetValue((UINT)num);
}

void GameUI::End()
{
	count = MAX_COUNT;
	curState = START;
	bossReadyTxt->Load();
}


