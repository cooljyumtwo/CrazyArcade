#pragma once
class Boss : public Monster
{
private:
	enum Type 
	{
		Octopus
	};
public:
	Boss(int key, float speed, bool isBubble = true, int hp = 1, Type type = Octopus);
	~Boss();

private:
	Type type;
};