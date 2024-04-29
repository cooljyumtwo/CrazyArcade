#include "Framework.h"
int WaitRoomUI::stageKey = 0;

WaitRoomUI::WaitRoomUI()
{
	CreateUIs();
	CreateMapSelectWindow();
	CreateMapSelectLineBtns();
	CreateBuffers();

	font = new ImageFont(PATH+L"/ResultNumber/");
	font->SetLocalPosition(CENTER);
	font->UpdateWorld();
	font->SetAligned(ImageFont::AlignedType::R);


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

	delete valueBuffer;
	delete outlineBuffer;
	delete font;

	for (MapSelectButton* mapSelectBtn : mapSelectLineBtns)
	{
		delete mapSelectBtn;
	}
	mapSelectLineBtns.clear();
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

	for (MapSelectButton* mapSelectBtn : mapSelectLineBtns)
	{
		mapSelectBtn->Update();
	}

	//PlayIntro();

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

	for (MapSelectButton* mapSelectBtn : mapSelectLineBtns)
	{
		mapSelectBtn->Render();
	}

	//font->Render();
}

void WaitRoomUI::PostRender()
{
	mapSelectLine->RenderUI();

	//ImGui::DragFloat("time", &outlineBuffer->Get()[0]);

	//int min = time / 60;
	//int second = (int)time % 60;

	//char str[100] = {};
	//sprintf_s(str, "%.2d : %.2d", min, second);
	//Font::Get()->RenderText(str, CENTER);
}

void WaitRoomUI::CreateUIs()
{
	//bgTexs
	bgTexs.resize(introBgs.size());

	FOR(introBgs.size())
		bgTexs[i] = Texture::Add(PATH + introBgs[i]);

	//bg
	bg = new Quad(PATH_WAITROOM + L"WaitRoomBG.png");
	bg->Translate(CENTER);
	bg->Update();

	mapSelectImg = new Quad(PATH_WAITROOM + L"Map1.png");
	mapSelectImg->SetTag("WaitRoom_MapSelectImg");
	mapSelectImg->Load();
	mapSelectImg->Update();


	//btn
	mapSelectBtn = new Button(PATH_WAITROOM + L"MapSelectBtn.png");
	mapSelectBtn->Translate(CENTER);
	mapSelectBtn->SetTag("WaitRoom_MapSelectBtn");
	mapSelectBtn->Load();
	mapSelectBtn->SetEvent([this]() {
		mapSelectWindow->SetActive(true);
		}); 
	//btn
	gameStartBtn = new Button(PATH_WAITROOM + L"GameStartBtn.png");
	gameStartBtn->Translate(CENTER);
	gameStartBtn->SetTag("WaitRoom_GameStartBtn");
	gameStartBtn->Load();
	gameStartBtn->SetEvent([this]() {
		SCENE->ChangeScene("Game");
		mapSelectWindow->SetActive(false);
		}); 

	//fade
	secondMap = Texture::Add(PATH + L"FadeWhite.png");
}

void WaitRoomUI::CreateMapSelectWindow()
{
	//bg
	mapSelectWindow = new Quad(PATH_WAITROOM + L"MapSelectWindow.png");
	mapSelectWindow->Translate(CENTER);
	mapSelectWindow->Update(); 

	mapSelectWindowMapImg = new Quad(PATH_WAITROOM + L"Map1.png");
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
	acceptBtn = new Button(PATH_WAITROOM + L"AcceptBtn.png");
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
	cancelBtn = new Button(PATH_WAITROOM + L"CancelBtn.png");
	cancelBtn->SetTag("WaitRoom_CancelBtn");
	cancelBtn->Load();
	cancelBtn->SetParent(mapSelectWindow);
	cancelBtn->SetEvent([this]() {
		mapSelectWindow->SetActive(false);
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

void WaitRoomUI::PlayIntro()
{
	frameTime += DELTA;

	if (frameTime > MAX_FRAME_TIME && count < MAX_FRAME_COUNT * 4)
	{
		frameTime -= MAX_FRAME_TIME;

		if (count >= MAX_FRAME_COUNT && count < MAX_FRAME_COUNT * 2)
		{
			outlineBuffer->Get()[0] -= 1;
			bg->GetMaterial()->SetTexture(bgTexs[1]);
		}
		else if (count >= MAX_FRAME_COUNT * 3)
		{
			outlineBuffer->Get()[0] -= 1;
			bg->GetMaterial()->SetTexture(bgTexs[2]);
			mapSelectBtn->SetActive(true);
		}
		else
			outlineBuffer->Get()[0] += 1;
		count++;
	}

	if (count > MAX_FRAME_COUNT * 4)
		isEndIntro = true;
}
