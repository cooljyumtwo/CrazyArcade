#pragma once

class BossHit : public CharacterAction
{
public:
    BossHit(Transform* target, int key);

    void End() override;
};