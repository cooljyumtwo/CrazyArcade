#pragma once

class CookieMelee : public CookieAction
{
public:
    CookieMelee(Transform* target);

    void Update() override;
    void Render() override;

private:
    void ActiveCollider();
    void InactiveCollider();
    void AttackEnd();

private:
    RectCollider* attackCollider;
};