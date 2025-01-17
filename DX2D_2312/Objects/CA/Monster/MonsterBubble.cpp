#include "Framework.h"

MonsterBubble::MonsterBubble(Transform* target, int key, int max_frameX)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Bubble.png", max_frameX, 1, true);
}

void MonsterBubble::Start()
{
	Monster* monster = (Monster*)target;
	if (monster->GetIsBoss())
	{
		if (!Audio::Get()->IsPlaySound("BossBubble"))
			Audio::Get()->Play("BossBubble");
	}
}
