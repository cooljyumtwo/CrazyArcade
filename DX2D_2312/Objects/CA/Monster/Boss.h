#pragma once
class Boss : public Monster
{
private:
	const wstring PATH = L"ResourcesCA/Textures/Character/Monster/";
	enum Type 
	{
		Octopus
	};
public:
	Boss(int key, float speed, bool isBubble = true, int hp = 1, Type type = Octopus);
	~Boss();

	void Update() override;

	void PostRender();

private:
	int maxHp;
	Type type;
	ProgressBar* hpBar;

	float playTime = 0.0f;
	float attackTime = 5.0f;

};