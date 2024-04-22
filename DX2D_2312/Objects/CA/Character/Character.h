#pragma once

class Character : public GameObject
{
private:
    vector<int> MAX_STAT = { 7, 5, 5 };

public:
    enum State
    {
        IDLE, MOVE, BUBBLE, ALIVE, DIE
    };

    struct Stat 
    {
        int bubbleCnt = 1;
        int bubblePower = 2;
        int speed = 1;
    };

public:
    Character();
    ~Character();

    void Update();
    void Render(); 
    void PostRender();
    float GetDepth() override;

    void UpdateWorld() override;

    RectCollider* GetCollider() { return collider; }

    void SetAction(int state);

    void MinusBubbleCurCnt() { if (bubbleCurCnt > 0) bubbleCurCnt--; }

    Stat GetStat() { return stat; }

private:
    void Move();
    void Attack();
    void Bubble();

    void Landing();

    void CreateActions();

    void AddAction(string file, int frameX, int frameY);

protected:
    Stat stat;

private:
    RectCollider* collider;

    map<State, Action*> actions;

    State curState = IDLE;

    Vector2 posIdx;

    int bubbleCurCnt = 0;
};