#pragma once

class Effect : public GameObject
{
private:
    const float FPS = 10.0f;
    const wstring PATH = L"ResourcesCA/Textures/Effect/";

public:
    Effect(wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive);
    ~Effect();

    void Update() override;
    void Render() override;

    void Play(const Vector2& pos);
    void End();

private:
    FrameBuffer* frameBuffer;

    float delayTime = 1.0f / FPS;
    float frameTime = 0.0f;
    float speed;

    UINT curFrameNum = 0;
    UINT maxFrameNum = 0;

    Vector2 curFrame;
    Vector2 maxFrame;

    bool isAdditive;

    Action* action;
};