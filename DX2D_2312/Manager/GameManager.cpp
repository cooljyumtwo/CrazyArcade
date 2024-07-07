#include "Framework.h"
#include "Scenes/CA/StartScene.h"
#include "Scenes/CA/WaitRoomScene.h"
#include "Scenes/CA/MapEditScene.h"
#include "Scenes/CA/GameScene.h"

bool GameManager::isDraw = false; //화면 그릴지 말지 //전역 변수
bool GameManager::isGUI = false; //GUI Editor 킬지 말지 //전역 변수

GameManager::GameManager() //생성자
{
	Create();

	SCENE->Add("Start", new StartScene());
	SCENE->Add("WaitRoom", new WaitRoomScene());
	SCENE->Add("MapEdit", new MapEditScene());
	SCENE->Add("Game", new GameScene());

	UIManager::Get()->Add("Start", new StartUI());
	UIManager::Get()->Add("WaitRoom", new WaitRoomUI());
	UIManager::Get()->Add("MapEdit", new MapEditUI());
	UIManager::Get()->Add("Game", new GameUI());

	SCENE->ChangeScene("Start");

	ShowCursor(false); //마우스 커서 안보이게 설정
}

GameManager::~GameManager() //소멸자
{
	Delete();
}

void GameManager::Update()
{
	Audio::Get()->Update();
	Keyboard::Get()->Update();
	Timer::Get()->Update();

	Environment::Get()->Update();
	UIManager::Get()->Update();

	SCENE->Update();

	if (KEY->Down(VK_F2))
		OnDraw();

	if (KEY->Down(VK_F3))
		SCENE->ChangeScene("WaitRoom");	

	if (KEY->Down(VK_F4))
		SCENE->ChangeScene("MapEdit");
	
	if (KEY->Down(VK_F5))
		SCENE->ChangeScene("Game");

	if (KEY->Down(VK_F6))
	{
		isGUI = !isGUI;
	}

	cursor->SetLocalPosition(mousePos + CURSOR_OFFSET);
	cursor->Update();
}

void GameManager::Render()
{
	UIManager::Get()->PreRender();
	SCENE->PreRender();

	Environment::Get()->SetViewport();
	Environment::Get()->SetProjection();

	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (isGUI) 
	{
		ImGui::Begin("Edit", &isGUI, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	}

	Font::Get()->SetColor("Yellow");
	Font::Get()->SetStyle("FPS");

	Font::Get()->GetDC()->BeginDraw();

	if (isDraw) 
	{
		string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
		Font::Get()->RenderText(fps, { 0, SCREEN_HEIGHT - 10 });
	}
	
	Font::Get()->SetStyle("Default");

	UIManager::Get()->Render();
	SCENE->Render();
	
	Font::Get()->GetDC()->EndDraw();
	UIManager::Get()->PostRender();

	if (isGUI) 
	{
		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	cursor->Render();

	Device::Get()->Present();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Environment::Get();
	Font::Get();
	UIManager::Get();
	Audio::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddColor("Yellow", 1, 1, 0);
	Font::Get()->AddColor("Black", 0, 0, 0);
	Font::Get()->AddStyle("Default", L"Open Sans",10);
	Font::Get()->AddStyle("FPS", L"Open Sans",20);
	Font::Get()->AddStyle("NickName", L"Quicksand", 20);
	Font::Get()->AddStyle("Button", L"Quicksand", 20,
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_FAR);

	cursor = new Button(L"ResourcesCA/Textures/UI/Etc/MouseImg.png");
}

void GameManager::Delete()
{
	SceneManager::Delete();
	Keyboard::Delete();
	Timer::Delete();
	Font::Delete();
	Audio::Delete();

	Shader::Delete();
	Texture::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
