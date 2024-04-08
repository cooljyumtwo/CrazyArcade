#include "Framework.h"

Bullet::Bullet(wstring textureFile, Vector2 startUV, Vector2 endUV)
	: Quad(textureFile, true, startUV, endUV)
{
	SetActive(false);
}

Bullet::~Bullet()
{
	delete collider;
}

void Bullet::Update()
{
	UpdateWorld();
	collider->UpdateWorld();
}

void Bullet::Render()
{
	Quad::Render();
	collider->Render();
}

void Bullet::Fire(const Vector2& pos, const Vector2& direction, float power, float speed)
{
	SetActive(true);

	data.power = power;
	data.speed = speed;

	SetLocalPosition(pos);
	localRotation.z = direction.Angle();
	UpdateWorld();
}

void Bullet::Fire(const Vector2& pos, const Vector2& direction, SkillData data)
{
	SetActive(true);

	SetLocalPosition(pos);
	localRotation.z = direction.Angle();
	UpdateWorld();

	this->data = data;

	switch (data.level)
	{
	case 1:
		material->GetColor()->SetColor(1, 1, 1);
		break;
	case 2:
		material->GetColor()->SetColor(1, 1, 0);
		break;
	case 3:
		material->GetColor()->SetColor(0, 1, 0);
		break;
	case 4:
		material->GetColor()->SetColor(0, 1, 1);
		break;
	case 5:
		material->GetColor()->SetColor(1, 0, 0);
		break;
	}
}
