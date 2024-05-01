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

    void LoadBossMonster();
    void Spawn(const Vector2& pos);
    void BossSpawn(const Vector2& pos);

    void LoadMonster();
    void ClearMonster();
    void Collision(Character* character);

    void SetIsRoad() { isRoad = !isRoad; }

    void AddKillMonster(bool isBoss = false);

private:
    int sizeItemDatas;
    int totalProbability = 0;

    bool isRoad = true;
    Boss* boss;

    int killMonster = 0;
    int spawnMonster = 0;
    int cntBoss = 0;
};