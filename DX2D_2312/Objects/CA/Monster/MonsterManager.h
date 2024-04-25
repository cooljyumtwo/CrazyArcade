#pragma once

class MonsterManager : public PoolingManager<Monster>, public Singleton<MonsterManager>
{
private:
    friend class Singleton;

    MonsterManager();
    ~MonsterManager();

public:
    void Update();
    void Render();

    void Spawn(const Vector2& pos);

    void Collision(Character* target);

private:
    int sizeItemDatas;
    int totalProbability = 0;
};