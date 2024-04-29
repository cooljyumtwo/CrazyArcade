#include "Framework.h"

WaitRoomUI::WaitRoomUI()
{
	CreateUIs();
	CreateBuffers();

	font = new ImageFont(L"Resources/Textures/UI/Numbers/");
	font->SetLocalPosition(CENTER);
	font->UpdateWorld();
	font->SetAligned(ImageFont::AlignedType::R);

}

WaitRoomUI::~WaitRoomUI()
{
	delete bg;
	delete startBtn;
	delete valueBuffer;
	delete outlineBuffer;
	delete font;
}

void WaitRoomUI::Update()
{
	time += DELTA * 10.0f;
	font->SetValue((UINT)time);

	startBtn->Update();

	if (isEndIntro) return;

	PlayIntro();

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
	startBtn->Render();
}

void WaitRoomUI::PostRender()
{
	startBtn->RenderUI();

	ImGui::DragFloat("time", &outlineBuffer->Get()[0]);

	int min = time / 60;
	int second = (int)time % 60;

	char str[100] = {};
	sprintf_s(str, "%.2d : %.2d", min, second);
	Font::Get()->RenderText(str, CENTER);
}

void WaitRoomUI::CreateUIs()
{
	//bgTexs
	bgTexs.resize(introBgs.size());

	FOR(introBgs.size())
		bgTexs[i] = Texture::Add(PATH + introBgs[i]);

	//bg
	bg = new Quad(Vector2{ SCREEN_WIDTH, SCREEN_HEIGHT });
	bg->Translate(CENTER);
	bg->GetMaterial()->SetPixelShader(L"Multi.hlsl");
	bg->GetMaterial()->SetTexture(bgTexs[0]);
	bg->Update();

	//btn
	startBtn = new Button(PATH + L"GameStartBtn.png");
	startBtn->Translate(CENTER);
	startBtn->SetTag("Start_StartBtn");
	startBtn->Load();
	startBtn->SetActive(false);
	startBtn->GetMaterial()->SetPixelShader(L"Multi.hlsl");
	startBtn->SetEvent([]() {
		SCENE->ChangeScene("Game");
		});

	//fade
	secondMap = Texture::Add(PATH + L"FadeWhite.png");
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
			startBtn->SetActive(true);
		}
		else
			outlineBuffer->Get()[0] += 1;
		count++;
	}

	if (count > MAX_FRAME_COUNT * 4)
		isEndIntro = true;
}
