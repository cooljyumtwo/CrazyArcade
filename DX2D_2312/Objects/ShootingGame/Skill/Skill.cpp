#include "Framework.h"

Skill::Skill(int key, Transform* owner) : owner(owner)
{
	data = ShootingDataManager::Get()->GetSkillData(key);
}

Skill::~Skill()
{
}

void Skill::LevelUp()
{
	data = ShootingDataManager::Get()->GetSkillData(data.key + 1);
}

void Skill::SetData(int key)
{
	data = ShootingDataManager::Get()->GetSkillData(key);
}
