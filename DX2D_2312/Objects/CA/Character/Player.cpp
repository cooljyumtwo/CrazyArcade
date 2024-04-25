#include "Framework.h"

Player::Player() : Character()
{
    CreateActions();
    actions[curState]->Start();

    item = new Item();
}

Player::~Player()
{
    delete item;
}

void Player::AddItem(Item* item)
{
    Item::Type type = (Item::Type)item->GetData().type;
   
    if (type < Item::B_NEEDLE)
    {
        switch (type)
        {
        case Item::B_POWER:
            stat.bubblePower += item->GetData().value;
            if (stat.bubblePower > MAX_STAT[item->GetData().type]) 
                stat.bubblePower = MAX_STAT[item->GetData().type];
            break;
        case Item::B_CNTUP:
            stat.bubbleCnt += item->GetData().value;
            if (stat.bubbleCnt > MAX_STAT[item->GetData().type]) 
                stat.bubbleCnt = MAX_STAT[item->GetData().type];
            break;
        case Item::U_SPEED:
            stat.speed += item->GetData().value;
            if (stat.speed > MAX_STAT[item->GetData().type]) 
                stat.speed = MAX_STAT[item->GetData().type];
            break;
        default:
            break;
        }
    }
    else
        this->item->SetData(item->GetData());
}

void Player::Attack()
{

   // Character::Attack();
}
