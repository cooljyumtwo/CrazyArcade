#pragma once

class CookieJumpDouble : public CookieJumpUp
{
public:
    CookieJumpDouble(Transform* target);

    void Start() override;

private:
    void EndAction();
};