#pragma once

class MonsterDie : public CharacterAction
{

public:
    MonsterDie(Transform* target, int key);

    void End();
};