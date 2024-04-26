#pragma once

class MonsterMove : public CharacterAction
{
private:
    int MAX_SPEED = 5;

public:
    MonsterMove();
    MonsterMove(Transform* target, int key, float speed = 50.0f);

    void Update() override;

    void Move();
    void SetMoveTime();
    void RandomCompass();

    float playTime = 0.0f;
    float moveTime = 0.0f;
};