#include "Framework.h"

int WaitRoomUI::stageKey = 1;

WaitRoomUI::WaitRoomUI()
{
	CreateUIs();
	CreateMapSelectWindow();
	CreateMapSelectLineBtns();
	CreateBuffers();
	CreateFonts();

	fontpos = CENTER;
}

WaitRoomUI::~WaitRoomUI()
{
	delete bg;
	delete mapSelectImg;
	delete mapSelectBtn;
	delete gameStartBtn;

	delete mapSelectWindow;
	delete mapSelectWindowMapImg;
	delete mapSelectWindowMapTxt;
	delete acceptBtn;
	delete cancelBtn;
	delete mapEditBtn;
	delete exitBtn;

	delete valueBuffer;
	delete outlineBuffer;
	delete font;

	for (MapSelectButton* mapSelectBtn : mapSelectLineBtns)
	{
		delete mapSelectBtn;
	}
	mapSelectLineBtns.clear();
}

void WaitRoomUI::Start()
{
	mapSelectWindow->SetActive(false);
}

void WaitRoomUI::Update()
{
	time += DELTA * 10.0f;
	font->SetValue((UINT)10);

	mapSelectLine->Update();
	mapSelectBtn->Update();
	gameStartBtn->Update();
	acceptBtn->Update();
	cancelBtn->Update();
	mapEditBtn->Update();
	exitBtn->Update();
	cancelBtn->Update();
	mapEditBtn->Update();
	exitBtn->Update();
	bg->Update();

	for (MapSelectButton* mapSelectBtn : mapSelectLineBtns)
	{
		mapSelectBtn->Update();
	}
}

void WaitRoomUI::PreRender()
{
}

void WaitRoomUI::Render()
{
	valueBuffer->SetPS(1);
	outlineBuffer->SetPS(2);

	secondMap->PSSet(1);

	bg->Render();
	mapSelectImg->Render();
	mapSelectBtn->Render();
	gameStartBtn->Render();

	mapSelectWindow->Render();
	mapSelectWindowMapImg->Render();
	mapSelectWindowMapTxt->Render();
	mapSelectLine->Render();
	acceptBtn->Render();
	cancelBtn->Render();
	mapEditBtn->Render();
	exitBtn->Render();

	for (MapSelectButton* mapSelectBtn : mapSelectLineBtns)
	{
		mapSelectBtn->Render();
	}

	string id = "°­ÀÚ±è¹èÂî";
	Font::Get()->SetColor("Black");
	Font::Get()->RenderText(id, {48.0f, 392.0f});

}

void WaitRoomUI::PostRender()
{
	exitBtn->RenderUI();
	bg->RenderUI();
}

void WaitRoomUI::CreateUIs()
{
	//bg
	bg = new Quad(PATH_WAITROOM + L"WaitRoomBG.png");
	bg->Translate(CENTER);
	bg->SetTag("WaitRoom_BG");
	bg->Load();
	bg->Update();

	mapSelectImg = new Quad(PATH_WAITROOM + L"stage1-1.png");
	mapSelectImg->SetTag("WaitRoom_MapSelectImg");
	mapSelectImg->Load();
	mapSelectImg->Update();

	//btn
	mapSelectBtn = new Button(PATH_WAITROOM + L"MapSelectBtn.png", true);
	mapSelectBtn->Translate(CENTER);
	mapSelectBtn->SetTag("WaitRoom_MapSelectBtn");
	mapSelectBtn->Load();
	mapSelectBtn->SetEvent([this]() {
		mapSelectWindow->SetActive(true);
		}); 
	//btn
	gameStartBtn = new Button(PATH_WAITROOM + L"GameStartBtn.png", true);
	gameStartBtn->Translate(CENTER);
	gameStartBtn->SetTag("WaitRoom_GameStartBtn");
	gameStartBtn->Load();
	gameStartBtn->SetEvent([this]() {
		SCENE->ChangeScene("Game");
		mapSelectWindow->SetActive(false);
		}); 
	//btn
	exitBtn = new Button(PATH_WAITROOM + L"ExitBtn.png", true);
	exitBtn->Translate(CENTER);
	exitBtn->SetTag("WaitRoom_ExitBtn");
	exitBtn->Load();
	exitBtn->SetEvent([this]() {
		CloseWindow();
		});

	//fade
	secondMap = Texture::Add(PATH + L"FadeBlack.png");
}

void WaitRoomUI::CreateMapSelectWindow()
{
	//bg
	mapSelectWindow = new Quad(PATH_WAITROOM + L"MapSelectWindow.png");
	mapSelectWindow->Translate(CENTER);
	mapSelectWindow->Update(); 

	mapSelectWindowMapImg = new Quad(PATH_WAITROOM + L"stage1-1.png");
	mapSelectWindowMapImg->SetParent(mapSelectWindow);
	mapSelectWindowMapImg->SetTag("WaitRoom_MapSelectImgMapImg");
	mapSelectWindowMapImg->Load();
	mapSelectWindowMapImg->Update();

	mapSelectWindowMapTxt = new Quad(PATH_WAITROOM + L"PenguinMapTxt.png");
	mapSelectWindowMapTxt->SetParent(mapSelectWindow);
	mapSelectWindowMapTxt->SetTag("WaitRoom_MapSelectImgMapTxt");
	mapSelectWindowMapTxt->Load();
	mapSelectWindowMapTxt->Update();

	mapSelectLine = new MapSelectButton(PATH_WAITROOM + L"MapSelectLine.png");
	mapSelectLine->SetParent(mapSelectWindow);
	mapSelectLine->Update();
	mapSelectLine->SetLocalPosition(77.0f,113.0f);
	mapSelectLine->SetFont();


	//btn
	acceptBtn = new Button(PATH_WAITROOM + L"AcceptBtn.png", true);
	acceptBtn->SetTag("WaitRoom_AcceptBtn");
	acceptBtn->Load();
	acceptBtn->SetParent(mapSelectWindow);
	acceptBtn->SetEvent([this]() {
		stageKey = selectKey;
		mapSelectWindow->SetActive(false);
		StageData stageData = DataManager::Get()->GetStageData(stageKey);
		mapSelectImg->GetMaterial()->SetTexture(Texture::Add(PATH_WAITROOM + ToWString(stageData.stage1) + L".png"));
		});

	//btn
	cancelBtn = new Button(PATH_WAITROOM + L"CancelBtn.png", true);
	cancelBtn->SetTag("WaitRoom_CancelBtn");
	cancelBtn->Load();
	cancelBtn->SetParent(mapSelectWindow);
	cancelBtn->SetEvent([this]() {
		mapSelectWindow->SetActive(false);
		});

	//btn
	mapEditBtn = new Button(PATH_WAITROOM + L"EditBtn.png", true);
	mapEditBtn->SetTag("WaitRoom_MapEditBtn");
	mapEditBtn->Load();
	mapEditBtn->SetParent(mapSelectWindow);
	mapEditBtn->SetEvent([this]() {
		SCENE->ChangeScene("MapEdit");
		});

}

void WaitRoomUI::CreateBuffers()
{
	valueBuffer = new IntValueBuffer();
	valueBuffer->Get()[0] = 10;
	valueBuffer->Get()[2] = bg->GetSize().x;
	valueBuffer->Get()[3] = bg->GetSize().y;

	outlineBuffer = new FloatValueBuffer();
	outlineBuffer->Get()[0] = 0;
	outlineBuffer->Get()[1] = bg->GetSize().y;
	outlineBuffer->Get()[2] = bg->GetSize().x * 0.5f;
	outlineBuffer->Get()[3] = bg->GetSize().y * 0.5f;
}

void WaitRoomUI::CreateMapSelectLineBtns()
{
	int size = DataManager::Get()->SizeStageData();

	mapSelectLineBtns.resize(size);
	float lineIntervalY = 20.0f;
	FOR(size)
	{
		StageData stageData = DataManager::Get()->GetStageData(i);
		MapSelectButton* mapSelectLineBtn = new MapSelectButton(PATH_WAITROOM + L"MapSelectLine.png", stageData.key);
		mapSelectLineBtn->SetParent(mapSelectWindow);
		mapSelectLineBtn->Update();
		mapSelectLineBtn->SetLocalPosition(77.0f, 113.0f - (lineIntervalY * i));
		mapSelectLineBtn->SetFont(stageData.num);
		mapSelectLineBtn->SetEvent([this, mapSelectLineBtn]() {
			selectKey = mapSelectLineBtn->GetKey(); 
			StageData stageData = DataManager::Get()->GetStageData(selectKey);
			mapSelectWindowMapImg->GetMaterial()->SetTexture(Texture::Add(PATH_WAITROOM + ToWString(stageData.stage1)+ L".png"));
			});

		mapSelectLineBtns[i] = mapSelectLineBtn;
	}
}

void WaitRoomUI::CreateFonts()
{
	font = new ImageFont(PATH + L"/ResultNumber/");
	font->SetLocalPosition(CENTER);
	font->UpdateWorld();
	font->SetAligned(ImageFont::AlignedType::R);
}

void WaitRoomUI::PlayIntro()
{
	frameTime += DELTA;

	if (frameTime > MAX_FRAME_TIME && count < MAX_FRAME_COUNT * 2)
	{
		frameTime -= MAX_FRAME_TIME;

		if (count >= MAX_FRAME_COUNT )
		{
			DestroyWindow(hWnd);
		}
		else
			outlineBuffer->Get()[0] += 1;
		count++;
	}
}

void WaitRoomUI::CloseWindow()
{
	PlayIntro();
	DestroyWindow(hWnd);
}
