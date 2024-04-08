#pragma once

class RangeEnemy : public Enemy
{
private:
    const float FIRE_INTERVAL = 1.0f;

public:
    RangeEnemy();
    ~RangeEnemy();

protected:
    virtual void Move() override;

private:
    void Fire();

private:
    float time = 0.0f;
};