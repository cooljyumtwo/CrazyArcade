#pragma once

class Player : public Character
{
public:
    Player();
    ~Player();

    void AddItem(Item* item);

private:
    Item* item;
};