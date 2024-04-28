#include "Framework.h"

Boss::Boss(int key, float speed, bool isBubble, int hp, Type type) 
	: Monster(key, speed, isBubble, hp), type(type)
{
	actions[MOVE] = new MonsterMove(this, key, speed, 2);
	actions[HIT] = new BossHit(this, key);
}

Boss::~Boss()
{
}
 