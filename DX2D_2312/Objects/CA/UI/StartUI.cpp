#include "Framework.h"

StartUI::StartUI()
{
	CreateUIs();
	CreateBuffers();
}

StartUI::~StartUI()
{
	delete bg;
	delete startBtn;
	delete valueBuffer;
	delete outlineBuffer;
}

void StartUI::Update()
{
	startBtn->Update();

	if (isEndIntro) return;

	PlayIntro();
}

void StartUI::PreRender()
{
}

void StartUI::Render()
{
	valueBuffer->SetPS(1);
	outlineBuffer->SetPS(2);

	secondMap->PSSet(1);

	bg->Render();
	startBtn->Render();
}

void StartUI::PostRender()
{
	startBtn->RenderUI();

	ImGui::DragFloat("time", &outlineBuffer->Get()[0]);
}

void StartUI::CreateUIs()
{
	//bgTexs
	bgTexs.resize(introBgs.size());

	FOR(introBgs.size())
		bgTexs[i] = Texture::Add(PATH_START + introBgs[i]);

	//bg
	bg = new Quad(Vector2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	bg->Translate(CENTER);
	bg->GetMaterial()->SetPixelShader(L"Multi.hlsl");
	bg->GetMaterial()->SetTexture(bgTexs[0]);
	bg->Update();

	//btn
	startBtn = new Button(PATH_START + L"GameStartBtn.png");
	startBtn->Translate(CENTER);
	startBtn->SetTag("Start_StartBtn");
	startBtn->Load();
	startBtn->SetActive(false);
	startBtn->GetMaterial()->SetPixelShader(L"Multi.hlsl");
	startBtn->SetEvent([]() {
		SCENE->ChangeScene("WaitRoom");
		});

	//fade
	secondMap = Texture::Add(PATH_START + L"FadeWhite.png");
}

void StartUI::CreateBuffers()
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

void StartUI::PlayIntro()
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
			startBtn->SetActive(true);
		}
		else
			outlineBuffer->Get()[0] += 1;
		count++;
	}

	if (count > MAX_FRAME_COUNT * 4)
		isEndIntro = true;
}
