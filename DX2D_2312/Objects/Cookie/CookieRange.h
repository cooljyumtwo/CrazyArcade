#pragma once

class CookieRange : public CookieAction
{
public:
    CookieRange(Transform* target);

    void Start() override;

private:
    void Fire();
    void AttackEnd();
};