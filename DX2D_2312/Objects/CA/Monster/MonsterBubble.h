#pragma once

class MonsterBubble : public CharacterAction
{
public:
    MonsterBubble(Transform* target, int key);

    void Update() override;

};