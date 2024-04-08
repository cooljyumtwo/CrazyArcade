#include "Framework.h"

BaseBullet::BaseBullet(wstring textureFile, Vector2 startUV, Vector2 endUV)
	: Bullet(textureFile, startUV, endUV)
{
	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);
}

void BaseBullet::Update()
{
	if (!IsActive()) return;

	Translate(GetRight() * data.speed * DELTA);

	if (!CAM->ContainFrustum(this))
		SetActive(false);

	Bullet::Update();
}
