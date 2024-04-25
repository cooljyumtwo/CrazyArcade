#include "Framework.h"

Effect::Effect(wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive)
{
    SetActive(false);

    action = new Action();
    action->LoadClip(PATH + textureFile, 4, 1, false);
    action->GetClip(0)->SetEvent([this]() { End(); });
}

Effect::~Effect()
{
    delete frameBuffer;
}

void Effect::Update()
{
    if (!IsActive()) return;

    action->Update();
    UpdateWorld();

}

void Effect::Render()
{
    if (!IsActive()) return;

    GameObject::SetRender();
    action->Render();
}

void Effect::Play(const Vector2& pos)
{
    SetActive(true);
    SetGlobalPosition(pos);

    action->Start();
}

void Effect::End()
{
    SetActive(false);
}
