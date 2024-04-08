#include "Framework.h"

CookieBullet::CookieBullet()
    : BaseBullet(L"Resources/Textures/Cookie/Cookie_Bullet.png",
        Vector2(), Vector2(0.2f, 0.5f))
{
    material->SetPixelShader(L"Effect.hlsl");

    frameBuffer = new FloatValueBuffer();
    frameBuffer->Get()[0] = 5;
    frameBuffer->Get()[1] = 2;

    maxFrmae = 10;
}

void CookieBullet::Update()
{
    if (!IsActive()) return;

    playTime += DELTA;

    if (playTime >= FRAME_INTERVAL)
    {
        playTime -= FRAME_INTERVAL;

        ++curFrame %= maxFrmae;     

        frameBuffer->Get()[2] = curFrame % 5;
        frameBuffer->Get()[3] = curFrame / 5;
    }

    BaseBullet::Update();
}

void CookieBullet::Render()
{
    frameBuffer->SetPS(1);

    Bullet::Render();
}
