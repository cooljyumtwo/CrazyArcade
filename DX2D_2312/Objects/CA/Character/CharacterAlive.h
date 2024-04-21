#pragma once

class CharacterAlive : public CharacterAction
{
protected:

public:
    CharacterAlive(Transform* target);

    void Start();
    void End();

};