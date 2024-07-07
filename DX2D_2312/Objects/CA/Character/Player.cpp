#include "Framework.h"

Player::Player() : Character()
{
    CreateActions();
    actions[curState]->Start();

    collider->SetOffset(Vector2(0.0f,-5.0f));
    collider->SetSize({ Tile::TILE_SIZE - 10.0f, Tile::TILE_SIZE - 10.0f });

    item = new Item();

    playerPosArrow = new Quad(L"ResourcesCA/Textures/UI/Etc/PlayerArrow.png");
    playerPosArrow->SetParent(this);
    playerPosArrow->Translate(Vector2::Up() * Vector2 { 0, 40.0f });
}

Player::~Player()
{
    delete item;
    delete playerPosArrow;
}

void Player::Update()
{
    Character::Update();
    playerPosArrow->UpdateWorld();
}

void Player::PostRender()
{
    playerPosArrow->Render();
}

void Player::AddItem(Item* item)
{
    if (!Audio::Get()->IsPlaySound("ItemAdd"))
    {
        Audio::Get()->Play("ItemAdd");
    }

    Item::Type type = (Item::Type)item->GetData().type;

    UI* curUI = UIManager::Get()->GetUI("Game");
    GameUI* gameUI = (GameUI*)curUI;

    if (type < Item::B_NEEDLE)
    {
        switch (type)
        {
        case Item::B_POWER:
            stat.bubblePower += item->GetData().value;
            
            if (stat.bubblePower > MAX_STAT[item->GetData().type]) 
                stat.bubblePower = MAX_STAT[item->GetData().type];

            gameUI->SetStateFont(2, stat.bubblePower);
            break;
        case Item::B_CNTUP:
            stat.bubbleCnt += item->GetData().value;
            if (stat.bubbleCnt > MAX_STAT[item->GetData().type]) 
                stat.bubbleCnt = MAX_STAT[item->GetData().type];

            gameUI->SetStateFont(1, stat.bubbleCnt);
            break;
        case Item::U_SPEED:
            stat.speed += item->GetData().value;
            if (stat.speed > MAX_STAT[item->GetData().type])
            {
                stat.speed = MAX_STAT[item->GetData().type];
                isBubblePush = true;
            }
            gameUI->SetStateFont(3, stat.speed);
            break;
        case Item::B_PUSH:
            isBubblePush = true;
            break;
        default:
            break;
        }
    }
    else
    {
        this->item->SetData(item->GetData());
        
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

void Player::LoadPos(bool isSpawn)
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

    if (isSpawn) 
    {
        RemoveItem();
    }

    delete reader;

    isBubblePush = false;
    isEndSpawnAni = false;
    countSpawnEffect = 0;
    spawnTime = 0.0f;
}
