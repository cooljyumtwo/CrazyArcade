#pragma once

class UIManager : public Singleton<UIManager>
{
private:
    friend class Singleton;

    UIManager();
    ~UIManager();

public:
    void Update();
    void Render();

    void LevelUp();

    ProgressBar* GetExpBar() { return expBar; }
    Inventory* GetInventory() { return inventory; }

private:
    void ClickPause();
    void ClickInventory();
    void ClickLevelUp(int index);

    void CreateButton();
    void CreateProgressBar();
    void CreateSkillButton();    

    void Save();
    void Load();

private:
    ProgressBar* hpBar;
    ProgressBar* expBar;

    map<string, Button*> gameButtons;

    bool isPause = false;

    vector<Button*> skillLevelUpButtons;
    vector<Quad*> skillLevelUpImages;

    Inventory* inventory;
};