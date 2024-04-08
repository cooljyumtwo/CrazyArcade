#pragma once

class CookieAction : public Action
{
protected:
    const string PATH = "Resources/Textures/Cookie/";
    const float GRAVITY = 980.0f;
    const float MOVE_SPEED = 100.0f;

public:
    CookieAction() = default;
    CookieAction(string file, bool isLoop, float speed = 1.0f);
    ~CookieAction() = default;

    void SetTarget(Transform* target) { this->target = target; }

protected:
    void Move();

protected:
    Transform* target;
    Vector2 velocity;
};