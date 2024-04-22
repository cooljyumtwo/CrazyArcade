#pragma once

class ItemManager : public PoolingManager<Item>, public Singleton<ItemManager>
{
private:
    friend class Singleton;

    ItemManager();
    ~ItemManager();

public:
    void Spawn(const Vector2& pos);

    Item* Collision(Collider* collider);
};