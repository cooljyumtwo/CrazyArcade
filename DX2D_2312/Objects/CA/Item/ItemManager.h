#pragma once

class ItemManager : public PoolingManager<Item>, public Singleton<ItemManager>
{
private:
    friend class Singleton;

    ItemManager();
    ~ItemManager();

    void Update();
    void Render();
public:
    void Spawn(const Vector2& pos);

    Item* Collision(Collider* collider);
};