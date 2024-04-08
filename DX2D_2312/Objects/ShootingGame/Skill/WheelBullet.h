#pragma once

class WheelBullet : public Bullet
{
public:
    WheelBullet();

    void Update() override;

    void SetAngle(float angle) { this->angle = angle; }
    void SetOwner(Transform* transform) { owner = transform; }

private:
    float angle;
    Transform* owner;
};