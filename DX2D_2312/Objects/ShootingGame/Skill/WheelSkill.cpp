#include "Framework.h"

WheelSkill::WheelSkill(Transform* owner)
    : Skill(201, owner)
{
    wheelParent = new Transform();

    Bullet* bullet = BulletManager::Get()->Pop("WheelBullet");
    bullet->SetActive(true);
    bullet->SetParent(wheelParent);
    bullet->Translate(Vector2::Right() * data.range);
    bullet->SetData(data);

    wheels.push_back(bullet);
}

WheelSkill::~WheelSkill()
{
    delete wheelParent;
}

void WheelSkill::Update()
{
    wheelParent->SetLocalPosition(owner->GetGlobalPosition());
    wheelParent->Rotate(data.speed * DELTA);

    wheelParent->UpdateWorld();
}

void WheelSkill::Render()
{

}

void WheelSkill::LevelUp()
{
    for (GameObject* wheel : wheels)
        wheel->SetActive(false);

    Skill::LevelUp();

    float stepAngle = XM_2PI / data.amount;

    FOR(data.amount)
    {
        Bullet* bullet = BulletManager::Get()->Pop("WheelBullet");
        bullet->SetActive(true);
        bullet->SetParent(wheelParent);        
        bullet->SetData(data);

        Vector2 pos;
        pos.x = cos(stepAngle * i);
        pos.y = sin(stepAngle * i);

        bullet->SetLocalRotation(0, 0, 0);
        bullet->Rotate(pos.Angle());
        bullet->SetLocalPosition(pos * data.range);

        wheels.push_back(bullet);
    }
}
