#include "Framework.h"

MonsterBubble::MonsterBubble(Transform* target, int key)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Bubble.png", 2, 1, true);
}

void MonsterBubble::Update()
{
    CharacterAction::Update();
}
