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
            {
                stat.speed = MAX_STAT[item->GetData().type];
                isBubblePush = true;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        this->item->SetData(item->GetData());
        UI* curUI = UIManager::Get()->GetUI("Game");
        GameUI* gameUI = (GameUI*)curUI;
        gameUI->SetItemSlotImg(true, L"ResourcesCA/Textures/Item/" + item->GetData().textureFile);
    }
}

void Player::RemoveItem()
{
    ItemData data;
    item->SetData(data);

    UI* curUI = UIManager::Get()->GetUI("Game");
    GameUI* gameUI = (GameUI*)curUI;
    gameUI->SetItemSlotImg(false);
}

void Player::Attack()
{

   // Character::Attack();
}

void Player::LoadPos()
{
    BinaryReader* reader = new BinaryReader("ResourcesCA/TextData/Map/Player/" + TileManager::mapNameStr + ".map");

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    Vector2 curIdx = reader->Vector();
    Vector2 pos = TileManager::Get()->GetBgTile(curIdx)->GetGlobalPosition();
    SetLocalPosition(pos);

    delete reader;
}
