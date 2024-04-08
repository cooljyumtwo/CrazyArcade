#pragma once

class DashEnemy : public Enemy
{
private:
    const float IDLE_TIME = 1.0f;

public:
    DashEnemy();
    ~DashEnemy();

protected:
    virtual void Move() override;

private:
    void Dash();
    void StartDash();

private:
    Vector2 velocity;
    Vector2 startPos;

    Float4 dashColor = { 1, 0, 0, 1 };

    bool isMove = false;
    float time = IDLE_TIME;
    
};