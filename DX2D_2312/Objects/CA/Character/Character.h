#pragma once

class Character : public GameObject
{
    const int SPAWN_ANI_MAX_COUNT = 8;
    const float SPAWN_ANI_TIME = 0.3f;

public:
    enum State
    {
        IDLE, MOVE, BUBBLE, ALIVE, DIE, HIT, ATTACK
    };

protected:
    struct Stat 
    {
        int bubbleCnt = 3;
        int bubblePower = 1;
        int speed = 3;
    };

public:
    Character();
    ~Character();

    void Update();
    void Render(); 
    void PostRender();
    float GetDepth() override;

    void UpdateWorld() override;

    void SetInit();

    void SetAction(int state);

    void PlusBubbleCurCnt() { bubbleCurCnt++; }
    void MinusBubbleCurCnt() {  if (bubbleCurCnt > 0) bubbleCurCnt--; }

    Stat GetStat() { return stat; }

    void SpawnAni();

protected:
    void Move();
    void Attack();
    void Bubble();

    void Landing();

    virtual void CreateActions();

    void AddAction(string file, int frameX, int frameY);

protected:
    Stat stat;

    map<State, Action*> actions;

    State curState = IDLE;

    Vector2 posIdx;

    int bubbleCurCnt = 0;

    OutlineBuffer* outlineBuffer;

    float spawnTime = 0.0f;
    int countSpawnEffect = 0;

    bool isEndSpawnAni = false;
};