#pragma once

class Player : public Character
{
private:
    vector<int> MAX_STAT = { 2, 2, 2 };

public:
    Player();
    ~Player();

    void AddItem(Item* item);
    Item* GetItem() { return item; }
    void RemoveItem();

    void Attack();

    void LoadPos();

    bool GetIsBubblePush() { return isBubblePush; }


private:
    Item* item;
    bool isBubblePush = false;
};