#pragma once

class Character : public GameObject
{
public:
    enum State
    {
        IDLE, MOVE, BUBBLE, ALIVE, DIE, HIT
    };

protected:
    struct Stat 
    {
        int bubbleCnt = 1;
        int bubblePower = 1;
        int speed = 2;
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

    void PlusBubbleCurCnt() { bubbleCurCnt++; }
    void MinusBubbleCurCnt() {  if (bubbleCurCnt > 0) bubbleCurCnt--; }

    Stat GetStat() { return stat; }

protected:
    void Move();
    void Attack();
    void Bubble();

    void Landing();

    virtual void CreateActions();

    void AddAction(string file, int frameX, int frameY);

protected:
    Stat stat;

    RectCollider* collider;

    map<State, Action*> actions;

    State curState = IDLE;

    Vector2 posIdx;

    int bubbleCurCnt = 0;
};