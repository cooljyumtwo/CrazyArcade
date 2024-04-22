#include "Framework.h"

Player::Player() : Character()
{
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
            break;
        case Item::B_CNTUP:
            stat.bubbleCnt += item->GetData().value;
            break;
        case Item::U_SPEED:
            stat.speed += item->GetData().value;
            break;
        default:
            break;
        }
    }
    else
        this->item->SetData(item->GetData());
}
