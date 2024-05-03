#include "Framework.h"

#include "Scenes/CA/StartScene.h"
#include "Scenes/CA/WaitRoomScene.h"
#include "Scenes/CA/MapEditScene.h"
#include "Scenes/CA/GameScene.h"

bool GameManager::isDraw = false;
bool GameManager::isGUI = false;

GameManager::GameManager()
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

	ShowCursor(false);
}

GameManager::~GameManager()
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

	Font::Get()->SetColor("Red");
	Font::Get()->SetStyle("Default");

	Font::Get()->GetDC()->BeginDraw();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	//Font::Get()->RenderText(fps, { 0, SCREEN_HEIGHT - 10 });


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
	Font::Get()->AddColor("Red", 1, 0, 0);
	Font::Get()->AddColor("Black", 0, 0, 0);
	Font::Get()->AddStyle("Default", L"Open Sans",20);
	Font::Get()->AddStyle("NickName", L"Quicksand", 20);
	Font::Get()->AddStyle("Button", L"Quicksand", 20,
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_FAR);

	cursor = new Button(L"ResourcesCA/Textures/UI/Mouse/MouseImg.png");
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
