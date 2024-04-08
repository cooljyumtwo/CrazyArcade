#include "Framework.h"

RangeEnemy::RangeEnemy() : Enemy(ShootingDataManager::Get()->GetEnemyData(201))
{
}

RangeEnemy::~RangeEnemy()
{
}

void RangeEnemy::Move()
{
    float distance = direction.Magnitude();

    if (distance <= data.range)
    {
        Fire();
    }
    else
    {
        Enemy::Move();
    }
}

void RangeEnemy::Fire()
{
    time += DELTA;

    if (time > FIRE_INTERVAL)
    {
        time -= FIRE_INTERVAL;

        BulletManager::Get()->Fire(localPosition, direction, data.power, 200.0f);
    }
}
