#pragma once

class BossHit : public CharacterAction
{
public:
    BossHit(Transform* target, int key, int max_frameX = 2);

    void Start() override;
    void End() override;
};