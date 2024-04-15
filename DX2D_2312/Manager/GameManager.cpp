#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/ShootingGameScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/MapEditorScene.h"
#include "Scenes/PixelShaderScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/TileEditScene.h"
#include "Scenes/TileGameScene.h"
#include "Scenes/MapEditScene.h"
#include "Scenes/GameScene.h"


GameManager::GameManager()
{
	Create();

	//SCENE->Add("Start", new TutorialScene());
	//SCENE->Add("Start", new ShootingGameScene());
	//SCENE->Add("Start", new CollisionScene());
	//SCENE->Add("Start", new AnimationScene());
	//SCENE->Add("Start", new MapEditorScene());
	//SCENE->Add("Start", new PixelShaderScene());
	//SCENE->Add("Start", new RenderTargetScene());
	//SCENE->Add("Start", new TileEditScene());
	//SCENE->Add("Start", new TileGameScene());
	//SCENE->Add("Start", new MapEditScene());
	SCENE->Add("Start", new GameScene());
	//UIManager::Get()->Add("Start", new MapEditUI());
	UIManager::Get()->Add("Start", new GameUI());

	SCENE->ChangeScene("Start");
	UIManager::Get()->ChangeUI("Start");
}

GameManager::~GameManager()
{
	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();

	Environment::Get()->Update();
	//ObjectManager::Get()->Update();
	UIManager::Get()->Update();
	SCENE->Update();
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

	Font::Get()->SetColor("White");
	Font::Get()->SetStyle("Default");

	Font::Get()->GetDC()->BeginDraw();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	Font::Get()->RenderText(fps, { 0, SCREEN_HEIGHT - 10 });

	//ObjectManager::Get()->Render();
	UIManager::Get()->Render();
	SCENE->Render();


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::Get()->GetDC()->EndDraw();
	Device::Get()->Present();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Environment::Get();
	Font::Get();
	UIManager::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddColor("Black", 0, 0, 0);
	Font::Get()->AddStyle("Default", L"¹è¹Î À»Áö·Î10³âÈÄÃ¼");
	Font::Get()->AddStyle("Button", L"¸¼Àº °íµñ", 40,
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_FAR);
}

void GameManager::Delete()
{
	SceneManager::Delete();
	Keyboard::Delete();
	Timer::Delete();
	Font::Delete();

	Shader::Delete();
	Texture::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
