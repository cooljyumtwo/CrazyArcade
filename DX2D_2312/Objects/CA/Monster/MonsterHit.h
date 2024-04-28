#pragma once

class MonsterHit : public MonsterMove
{
private:
    int MAX_SPEED = 5;
    float MAX_HIT_TIME = 5.0f;

public:
    MonsterHit(Transform* target, int key, float speed = 50.0f);

    void Update() override;

private:
    RectCollider* HitCollider;

    float playHitTime = 0.0f;
};