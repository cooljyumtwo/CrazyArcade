#pragma once

class Upgrade : public Panel
{
public:
    Upgrade();
    ~Upgrade();

    void Update() override;
    void Render() override;

    void AddItem(void* item);

private:
    void CreateSlots();
    void RemoveItem(void* item);
    void Excute();

    bool IsCheck();

    void UpgradeSuccess();
    void UpgradeFail();

private:
    vector<Quad*> slots;
    vector<Item*> items;
    vector<Item*> selectItems;

    Button* excuteBtn;;

    int count = 0;
    int checkKey = 0;
};