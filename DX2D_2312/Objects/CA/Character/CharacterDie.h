#pragma once

class CharacterDie : public CharacterAction
{
protected:

public:
    CharacterDie(Transform* target);

    void Start();
    void End();
};