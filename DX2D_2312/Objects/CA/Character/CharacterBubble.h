#pragma once

class CharacterBubble : public CharacterAction
{
protected:

public:
    CharacterBubble(Transform* target);

    void Update() override;

    void Start();

    void Move();


private:
};