#pragma once

class Player : public Character
{
private:
    vector<int> MAX_STAT = { 2, 2, 2 };

public:
    Player();
    ~Player();

    void Update() override;
    void PostRender();

    void AddItem(Item* item);
    Item* GetItem() { return item; }
    void RemoveItem();

    void LoadPos(bool isSpawn = false);

    bool GetIsBubblePush() { return isBubblePush; }

private:
    Item* item;
    
    Quad* playerPosArrow;

    bool isBubblePush = true;
};