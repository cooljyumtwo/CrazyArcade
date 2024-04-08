#include "Framework.h"

Inventory::Inventory()
    : Panel(L"Resources/Textures/UI/InventoryPanel.png")
{
    CreateItemSlots();

    upgrade = new Upgrade();
    upgrade->SetParent(this);
    upgrade->SetLocalPosition(-size.x, 0);

    Observer::Get()->AddEvent("Save", bind(&Inventory::Save, this));
    Observer::Get()->AddEvent("Load", bind(&Inventory::Load, this));
}

Inventory::~Inventory()
{
    for (Quad* itemSlot : itemSlots)
        delete itemSlot;

    for(pair<int, Item*> item : items)
        delete item.second;

    delete upgrade;
}

void Inventory::Update()
{
    Panel::Update();

    for (Quad* itemSlot : itemSlots)
        itemSlot->Update();

    for (pair<int, Item*> item : items)
        item.second->Update();

    upgrade->Update();
}

void Inventory::Render()
{
    Panel::Render();

    for (Quad* itemSlot : itemSlots)
        itemSlot->Render();

    for (pair<int, Item*> item : items)
        item.second->Render();

    upgrade->Render();
}

void Inventory::AddItem(Item* item)
{
    int key = item->GetData().key;

    ObjectManager::Get()->Delete(item);

    if (items.count(key))
    {
        items[key]->AddCount(1);
        item->SetActive(false);
        return;
    }    

    item->SetParent(itemSlots[items.size()]);
    item->SetLocalPosition(0, 0);
    item->SetInven();    
    item->SetObjectEvent(bind(&Inventory::ClickItem, this, placeholders::_1), item);

    items[key] = item;
}

void Inventory::Save()
{
    BinaryWriter* writer = new BinaryWriter("Resources/TextData/Shooting/item.data");

    writer->UInt(items.size());

    for (auto item : items)
    {
        writer->Int(item.first);
        writer->Int(item.second->GetCount());
    }

    delete writer;
}

void Inventory::Load()
{
    BinaryReader* reader = new BinaryReader("Resources/TextData/Shooting/item.data");

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    UINT size = reader->UInt();

    FOR(size)
    {
        int key = reader->Int();
        int count = reader->Int();

        CreateItem(key, count);
    }

    delete reader;
}

void Inventory::CreateItemSlots()
{
    int colSize = 4;
    int rowSize = 4;

    itemSlots.reserve(colSize * rowSize);

    wstring file = L"Resources/Textures/UI/ItemSlot.png";
    Vector2 cellSize = size / Vector2(colSize, rowSize);

    Vector2 startPos = size* -0.5f + cellSize * 0.5f;

    for (int y = rowSize - 1; y >= 0; y--)
    {
        for (int x = 0; x < rowSize; x++)
        {
            Vector2 pos = startPos + cellSize * Vector2(x, y);

            Quad* itemSlot = new Quad(file, false);
            itemSlot->SetParent(this);
            itemSlot->SetLocalPosition(pos);

            itemSlots.push_back(itemSlot);
        }
    }
}

void Inventory::CreateItem(int key, int count)
{
    Item* item = ItemManager::Get()->Pop("Item", true);
    ObjectManager::Get()->Add(item);
    ItemData data = ShootingDataManager::Get()->GetItemData(key);
    item->Spawn({}, data);    
    item->AddCount(count - 1);

    AddItem(item);
}

void Inventory::Clear()
{
    unordered_map<int, Item*>::iterator iter = items.begin();

    for (; iter != items.end(); )
    {
        if (iter->second->GetCount() == 0)
        {
            ObjectManager::Get()->Add(iter->second);
            iter->second->SetActive(false);

            iter = items.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void Inventory::ClickItem(void* item)
{
    upgrade->AddItem(item);
}
