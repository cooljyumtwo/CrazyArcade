#pragma once

class CharacterMove : public CharacterAction
{
private:
    int MAX_SPEED = 5;

public:
    CharacterMove(Transform* target);

    void Update() override;

    void Move();

private:
    RectCollider* frontCollider;
};