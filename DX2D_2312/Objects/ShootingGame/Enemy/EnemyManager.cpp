#include "Framework.h"

EnemyManager::EnemyManager()
{
	totalObject["Melee"].resize(50);

	for (GameObject*& melee : totalObject["Melee"])
	{
		melee = new Enemy(ShootingDataManager::Get()->GetEnemyData(101));
		enemies.push_back((Enemy*)melee);
	}

	totalObject["Range"].resize(50);

	for (GameObject*& range : totalObject["Range"])
	{
		range = new RangeEnemy();
		enemies.push_back((Enemy*)range);
	}

	totalObject["Dash"].resize(50);

	for (GameObject*& range : totalObject["Dash"])
	{
		range = new DashEnemy();
		enemies.push_back((Enemy*)range);
	}
}

void EnemyManager::Update()
{
	playTime += DELTA;

	if (playTime >= SPAWN_INTERVAL)
	{
		playTime -= SPAWN_INTERVAL;

		int type = Random(0, 3);

		Enemy* enemy = nullptr;

		switch (type)
		{
		case 0:
			enemy = Pop("Range");
			break;
		case 1:
			enemy = Pop("Melee");
			break;
		case 2:
			enemy = Pop("Dash");
			break;
		}
				
		enemy->SetLocalPosition(GetRandomPos());		
		enemy->Spawn();
	}
}

void EnemyManager::SetTarget(Transform* transform)
{
	for (Enemy* enemy : enemies)
	{
		enemy->SetTarget(transform);
	}
}

GameObject* EnemyManager::GetClosestEnemy(const Vector2& pos)
{
	float minDistance = FLT_MAX;
	GameObject* minEnemy = nullptr;

	for (Enemy* enemy : enemies)
	{
		if (!enemy->IsActive()) continue;

		float distance = Distance(pos, enemy->GetGlobalPosition());

		if (distance < minDistance)
		{
			minDistance = distance;
			minEnemy = enemy;
		}
	}

	return minEnemy;
}

Vector2 EnemyManager::GetRandomPos()
{
	Direction direction = (Direction)Random(0, 4);

	float x = Random(0, SCREEN_WIDTH);
	float y = Random(0, SCREEN_HEIGHT);

	switch (direction)
	{
	case GameMath::Direction::UP:
		return CAM->GetGlobalPosition() + Vector2(x, SCREEN_HEIGHT);
	case GameMath::Direction::DOWN:
		return CAM->GetGlobalPosition() + Vector2(x, 0);
	case GameMath::Direction::LEFT:
		return CAM->GetGlobalPosition() + Vector2(0, y);
	case GameMath::Direction::RIGHT:
		return CAM->GetGlobalPosition() + Vector2(SCREEN_WIDTH, y);
	}

	return Vector2();
}
