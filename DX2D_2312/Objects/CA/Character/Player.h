#pragma once

class Player : public Character
{
private:
    vector<int> MAX_STAT = { 2, 2, 2 };

public:
    Player();
    ~Player();

    void AddItem(Item* item);
    void Attack();

    void Die();

private:
    Item* item;
};