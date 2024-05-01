#pragma once

class BossIdle : public CharacterAction
{
public:
    BossIdle(Transform* target, int key, int max_frameX = 2);
};