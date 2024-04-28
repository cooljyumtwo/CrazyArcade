#pragma once

class CharacterBubble : public CharacterAction
{
public:
    CharacterBubble(Transform* target);

    void Update() override;

    void Start();
    void End();


private:
    void Move();
    void Alive();
};