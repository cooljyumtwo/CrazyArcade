#pragma once

class CookieBullet : public BaseBullet
{
private:
    const float FRAME_INTERVAL = 0.1f;

public:
    CookieBullet();

    void Update() override;
    void Render() override;

private:
    float playTime = 0.0f;
    int curFrame = 0;
    int maxFrmae = 0;

    FloatValueBuffer* frameBuffer;
};