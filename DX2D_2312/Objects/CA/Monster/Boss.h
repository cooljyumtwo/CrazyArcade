#pragma once
class Boss : public Monster
{
private:
	const wstring PATH = L"ResourcesCA/Textures/Character/Monster/";
	enum Type 
	{
		Penguin
	};
public:
	Boss(int key, float speed, bool isBubble = true, int hp = 1, Type type = Penguin);
	~Boss();

	void Update() override;
	void Render() override;

	void Attack();

	void Hit(Collider* collider);

private:
	int maxHp;
	Type type;
	ProgressBar* hpBar;

	float playTime = 0.0f;
	float attackTime = 5.0f;
};