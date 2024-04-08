#include "Framework.h"

UIManager::UIManager()
{
	CreateButton();
	CreateProgressBar();
	CreateSkillButton();

	inventory = new Inventory();
	inventory->GetCloseBtn()->SetEvent(bind(&UIManager::ClickInventory, this));
	inventory->SetLocalPosition(SCREEN_WIDTH * 3 / 4, CENTER_Y);

	Load();
}

UIManager::~UIManager()
{	
	delete hpBar;
	delete expBar;
	delete inventory;

	for (auto button : gameButtons)
		delete button.second;
}

void UIManager::Update()
{
	inventory->Update();

	for (auto button : gameButtons)
		button.second->Update();

	for (Button* button : skillLevelUpButtons)
		button->Update();	
}

void UIManager::Render()
{
	for (auto button : gameButtons)
		button.second->Render();

	hpBar->Render();
	expBar->Render();
	inventory->Render();

	for (Button* button : skillLevelUpButtons)
		button->Render();

	for (Quad* image : skillLevelUpImages)
		image->Render();
}

void UIManager::LevelUp()
{
	for (Button* button : skillLevelUpButtons)
		button->SetActive(true);

	ClickPause();
}

void UIManager::ClickPause()
{
	Timer::Get()->SetScale(isPause);

	isPause = !isPause;

	gameButtons["Save"]->SetActive(isPause);
	gameButtons["Load"]->SetActive(isPause);
}

void UIManager::ClickInventory()
{
	Timer::Get()->SetScale(isPause);
	
	isPause = !isPause;	

	inventory->SetActive(isPause);
}

void UIManager::CreateButton()
{
	Button* button = new Button(L"Resources/Textures/UI/blue_button.png");
	button->SetEvent(bind(&UIManager::ClickPause, this));
	button->SetLocalPosition(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100);
	button->SetText("||");

	gameButtons["Pause"] = button;

	button = new Button(L"Resources/Textures/UI/InventoryIcon.png");
	button->SetEvent(bind(&UIManager::ClickInventory, this));
	button->SetLocalPosition(SCREEN_WIDTH - 100, 100);

	gameButtons["Iventory"] = button;

	button = new Button(L"Resources/Textures/UI/InventoryIcon.png");
	button->SetEvent(bind(&UIManager::ClickInventory, this));
	button->SetLocalPosition(SCREEN_WIDTH - 100, 100);	

	gameButtons["Iventory"] = button;

	button = new Button();
	button->SetEvent(bind(&UIManager::Save, this));
	button->SetLocalPosition(CENTER_X, CENTER_Y + 100);
	button->SetText("Save");
	button->SetActive(false);

	gameButtons["Save"] = button;

	button = new Button();
	button->SetEvent(bind(&UIManager::Load, this));
	button->SetLocalPosition(CENTER_X, CENTER_Y - 100);
	button->SetText("Load");
	button->SetActive(false);

	gameButtons["Load"] = button;
}

void UIManager::CreateProgressBar()
{
	wstring hpFront = L"Resources/Textures/UI/hp_bar.png";
	wstring hpBack = L"Resources/Textures/UI/hp_bar_BG.png";

	hpBar = new ProgressBar(hpFront, hpBack);
	hpBar->SetLocalPosition({ CENTER_X, SCREEN_HEIGHT * 0.9f });
	hpBar->UpdateWorld();

	hpFront = L"Resources/Textures/UI/expFront.png";
	hpBack = L"Resources/Textures/UI/expBack.png";

	expBar = new ProgressBar(hpFront, hpBack);
	expBar->SetLocalPosition({ CENTER_X, SCREEN_HEIGHT * 0.1f });
	expBar->SetAmount(0.0f);
	expBar->UpdateWorld();
}

void UIManager::CreateSkillButton()
{
	int skillCount = 2;

	float size = SCREEN_WIDTH / skillCount;

	FOR(skillCount)
	{
		Button* skillBtn = new Button(L"Resources/Textures/UI/SkillPanel.png");
		skillBtn->SetIntEvent(bind(&UIManager::ClickLevelUp, this, placeholders::_1), i);
		
		Vector2 pos = { size * 0.5f + size * i, CENTER_Y };
		skillBtn->SetLocalPosition(pos);
		skillBtn->UpdateWorld();
		skillBtn->SetActive(false);

		int key = (i + 1) * 100 + 1;

		wstring file = L"Resources/Textures/Shooting/" +
			ToWString(ShootingDataManager::Get()->GetSkillData(key).name);
		Quad* image = new Quad(file, false);
		image->SetParent(skillBtn);
		image->UpdateWorld();

		skillLevelUpButtons.push_back(skillBtn);
		skillLevelUpImages.push_back(image);
	}	
}

void UIManager::Save()
{
	Observer::Get()->ExcuteEvent("Save");
}

void UIManager::Load()
{
	Observer::Get()->ExcuteEvent("Load");
}

void UIManager::ClickLevelUp(int index)
{
	Observer::Get()->ExcuteIntEvent("SkillLevelUp", index);

	for (Button* button : skillLevelUpButtons)
		button->SetActive(false);

	ClickPause();
}
