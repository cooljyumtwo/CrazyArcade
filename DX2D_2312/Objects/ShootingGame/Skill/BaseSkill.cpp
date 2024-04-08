#include "Framework.h"

BaseSkill::BaseSkill(Transform* owner) : Skill(101, owner)
{
}

BaseSkill::~BaseSkill()
{
}

void BaseSkill::Update()
{
	time += DELTA;

	target = EnemyManager::Get()->GetClosestEnemy(owner->GetGlobalPosition());

	Rotate();

	if (time >= data.duration)
	{
		time -= data.duration;

		Fire();
	}
}

void BaseSkill::Render()
{
}

void BaseSkill::Fire()
{
	if (target == nullptr) return;

	Vector2 pos = ((Plane*)owner)->GetCursor()->GetGlobalPosition();
	//Vector2 dir = (target->GetGlobalPosition() - pos).Normalized();
	Vector2 dir = owner->GetRight();

	BulletManager::Get()->Fire(pos, dir, data);
}

void BaseSkill::Rotate()
{
	if (target == nullptr) return;

	Vector2 direction = target->GetGlobalPosition() - owner->GetGlobalPosition();
	float cross = Vector2::Cross(owner->GetRight(), direction);

	if (cross > EPSILON)
		owner->Rotate(rotSpeed * DELTA);
	else if(cross < -EPSILON)
		owner->Rotate(-rotSpeed * DELTA);
}
