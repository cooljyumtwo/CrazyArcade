#include "Framework.h"

DashEnemy::DashEnemy() : Enemy(ShootingDataManager::Get()->GetEnemyData(305))
{
}

DashEnemy::~DashEnemy()
{
}

void DashEnemy::Move()
{
    if (isMove)
    {
        Dash();
        return;
    }

    time += DELTA;

    if (time >= IDLE_TIME)
    {
        time -= IDLE_TIME;

        StartDash();
    }
}

void DashEnemy::Dash()
{
    Translate(velocity * data.speed * DELTA);

    float distance = Distance(startPos, localPosition);

    if (distance >= data.range)
    {
        isMove = false;
        material->GetColor()->SetColor(1, 1, 1);
    }
}

void DashEnemy::StartDash()
{
    isMove = true;
    startPos = localPosition;
    velocity = direction.Normalized();
    localRotation.z = velocity.Angle();

    material->GetColor()->SetColor(dashColor);
}
