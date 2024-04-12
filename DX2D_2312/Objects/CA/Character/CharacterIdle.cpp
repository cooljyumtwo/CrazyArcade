#include "Framework.h"

CharacterIdle::CharacterIdle()
{
    LoadClip(ToWString(PATH) + L"Bazzi/Idle_Down.png", 1, 1, false);
    LoadClip(ToWString(PATH) + L"Bazzi/Idle_Up.png", 1, 1, false);
    LoadClip(ToWString(PATH) + L"Bazzi/Idle_Right.png", 1, 1, false);
    LoadClip(ToWString(PATH) + L"Bazzi/Idle_Left.png", 1, 1, false);
}
