#include "Framework.h"

Effect::Effect(wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive)
    : Quad(textureFile, true, Vector2(),
        Vector2(1 / maxFrame.x, 1 / maxFrame.y)),
    speed(speed), isAdditive(isAdditive), maxFrame(maxFrame)
{
    material->SetPixelShader(L"Effect.hlsl");

    SetActive(false);

    frameBuffer = new FrameBuffer();
    frameBuffer->SetMaxFrame(maxFrame);

    maxFrameNum = (UINT)(maxFrame.x * maxFrame.y);    
}

Effect::~Effect()
{
    delete frameBuffer;
}

void Effect::Update()
{
    if (!IsActive()) return;

    frameTime += DELTA;

    if (frameTime >= delayTime)
    {
        frameTime -= delayTime;

        curFrameNum++;

        curFrame.x = curFrameNum % (int)maxFrame.x;
        curFrame.y = curFrameNum / (int)maxFrame.x;

        frameBuffer->SetCurFrame(curFrame);

        if (curFrameNum >= maxFrameNum)
            End();
    }

    UpdateWorld();
}

void Effect::Render()
{
    if (isAdditive)
        Environment::Get()->SetAdditiveBlend();

    frameBuffer->SetPS(1);
    Quad::Render();

    Environment::Get()->SetAlphaBlend();
}

void Effect::Play(const Vector2& pos)
{
    SetActive(true);
    SetLocalPosition(pos);

    frameTime = 0.0f;
    curFrameNum = 0;

    frameBuffer->SetCurFrame(Vector2());
}

void Effect::End()
{
    SetActive(false);
}
