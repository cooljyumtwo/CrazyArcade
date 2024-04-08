#pragma once

class CookieJump : public CookieAction
{
protected:
    const float JUMP_POWER = 600.0f;
    const float FLOOR_EPSILON = 2.0f;

public:
    CookieJump() = default;
    ~CookieJump() = default;

    virtual void Update() override;

protected:
    bool IsCollisionFloor();
};