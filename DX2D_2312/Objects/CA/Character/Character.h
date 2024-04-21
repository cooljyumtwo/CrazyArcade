#pragma once

class Character : public GameObject
{
public:
    enum State
    {
        IDLE, MOVE, BUBBLE, ALIVE,DIE//,INCARCERATION, LIVE, DIE
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

private:
    void Move();
    void Jump();
    void Attack();
    void Bubble();

    void Landing();

    void CreateActions();

    void AddAction(string file, int frameX, int frameY);


private:

    RectCollider* collider;

    map<State, Action*> actions;

    State curState = IDLE;

    Vector2 posIdx;
};