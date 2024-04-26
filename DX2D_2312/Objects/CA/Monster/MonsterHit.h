#pragma once

class MonsterHit : public MonsterMove
{
private:
    int MAX_SPEED = 5;

public:
    MonsterHit(Transform* target, int key, float speed = 50.0f);
};