#pragma once

class Inventory : public Panel
{
public:
    Inventory();
    ~Inventory();

    void Update() override;
    void Render() override;

    void AddItem(Item* item);

    void Save();
    void Load();

    void CreateItem(int key, int count);

    void Clear();
private:
    void CreateItemSlots();    

    void ClickItem(void* item);

private:
    vector<Quad*> itemSlots;
    unordered_map<int, Item*> items;

    Upgrade* upgrade;
};