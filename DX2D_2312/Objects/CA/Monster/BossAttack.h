#pragma once

class BossAttack : public CharacterAction
{
public:
    BossAttack(Transform* target, int key, int max_frameX = 2);

    void End() override;

};