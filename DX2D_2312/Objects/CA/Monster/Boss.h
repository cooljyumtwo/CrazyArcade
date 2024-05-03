#pragma once
class Boss : public Monster
{
private:
	const wstring PATH = L"ResourcesCA/Textures/Character/Monster/";

	enum Type 
	{
		Penguin
	};

	enum ModeState
	{
		NORMAL, ANGRY
	};

	const float NORMAL_ATTACk_TIME = 10.0f;
	const float ANGRY_STAY_TIME = 5.0f;

public:
	Boss(int key, float speed, bool isBubble = true, int hp = 1, Type type = Penguin);
	~Boss();

	void Update() override;
	void Render() override;

	void Attack();

	void CheckTileHit() override;
	void Hit(Collider* collider);

	void CheckMode();

private:
	int maxHp;

	Type type;
	ProgressBar* hpBar;

	ModeState modeState = NORMAL;

	float playTime = 0.0f;
	float attackTime = NORMAL_ATTACk_TIME;
};