#pragma once

class MonsterManager : public PoolingManager<Monster>, public Singleton<MonsterManager>
{
private:
    const string PATH = "ResourcesCA/TextData/Map/Monster/";
    const int CHECK_BOSS_IDX = 100;
private:
    friend class Singleton;

    MonsterManager();
    ~MonsterManager();

public:
    void Update();
    void Render();

    void LoadBossMonster();
    void Spawn(const Vector2& pos);

    void LoadMonster();
    void ClearMonster();
    void Collision(Character* character);
    bool Collision(Tile* tile);

    void SetIsRoad() { isRoad = !isRoad; }

    void AddKillMonster(bool isBoss = false);

    bool GetIsSpawnBoss() { return isSpawnBoss; }

private:
    int sizeItemDatas;
    int totalProbability = 0;

    bool isRoad = true;
    bool isSpawnBoss = false;

    int killMonster = 0;
    int spawnMonster = 0;
    int cntBoss = 0;
};