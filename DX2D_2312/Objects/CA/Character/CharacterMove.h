#pragma once

class CharacterMove : public CharacterAction
{
protected:

public:
    CharacterMove(Transform* target);

    void Update() override;

    void Move();
};