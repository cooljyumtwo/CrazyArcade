#pragma once

class Character : public GameObject
{
    const int SPAWN_ANI_MAX_COUNT = 5;
    const float SPAWN_ANI_TIME = 0.3f;
    const float INVINCIBLE_DURATION = 3.0f;  // 3초 동안 무적

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

    void Update() override;
    void Render() override;

    float GetDepth() override;

    void UpdateWorld() override;

    void SetInit();

    void SetAction(int state);

    void PlusBubbleCurCnt() { bubbleCurCnt++; }
    void MinusBubbleCurCnt() {  if (bubbleCurCnt > 0) bubbleCurCnt--; }

    Stat GetStat() { return stat; }

    void SpawnAni();

    void Die();


protected:
    void Move();
    void Attack();
    void Bubble();

    virtual void CreateActions();

    void AddAction(string file, int frameX, int frameY);

    void UpdateInvincibility();

protected:
    Stat stat;

    map<State, Action*> actions;

    State curState = IDLE;

    Vector2 posIdx;

    OutlineBuffer* outlineBuffer;

    float spawnTime = 0.0f;
    float invincibleTime = 0.0f;

    int bubbleCurCnt = 0;
    int countSpawnEffect = 0;

    bool isEndSpawnAni = false;
    bool isInvincible = false;
};