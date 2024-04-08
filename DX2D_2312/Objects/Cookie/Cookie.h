#pragma once

class Cookie : public GameObject
{
public:
    enum State
    {
        IDLE, RUN, 
        JUMP_UP = 10, JUMP_DOWN, JUMP_DOUBLE,
        RANGE = 20, MELEE, JUMP_ATTACK
    };

public:
    Cookie();
    ~Cookie();

    void Update() override;
    void Render() override;
    void PostRender();

    RectCollider* GetCollider() { return collider; }
    bool IsAir() { return jumpCount > 0; }

private:
    void Move();
    void Jump();   
    void Attack();

    void Landing();

    void SetAction(int state);

    void CreateActions();

private:
    OutlineBuffer* outlineBuffer;

    RectCollider* collider;

    map<State, Action*> actions;

    State curState = IDLE;

    int jumpCount = 0;
};