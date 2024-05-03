#pragma once

class ItemManager : public PoolingManager<Item>, public Singleton<ItemManager>
{
private:
    friend class Singleton;

    ItemManager();
    ~ItemManager();

public:
    void Update();
    void Render();

    void SetTotalProbability();

    void Spawn(const Vector2& pos);

    void Collision(Character* target);
    
    void ClearItems();

private:
    int sizeItemDatas;
    int totalProbability = 0;
};