#pragma once

class MonsterDie : public CharacterAction
{

public:
    MonsterDie(Transform* target, int key, int max_frameX = 2);

    void End();
};