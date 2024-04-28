#pragma once

class MonsterManager : public PoolingManager<Monster>, public Singleton<MonsterManager>
{
private:
    const string PATH = "ResourcesCA/TextData/Map/Monster/";
private:
    friend class Singleton;

    MonsterManager();
    ~MonsterManager();

public:
    void Update();
    void Render();

    void Spawn(const Vector2& pos);

    void LoadMonster();
    void ClearMonster();

private:
    int sizeItemDatas;
    int totalProbability = 0;

    Boss* boss;
};