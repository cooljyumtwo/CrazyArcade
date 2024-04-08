#pragma once

class BaseBullet : public Bullet
{
public:
    BaseBullet(wstring textureFile, Vector2 startUV = Vector2(),
        Vector2 endUV = Vector2(1, 1));

    void Update() override;
};