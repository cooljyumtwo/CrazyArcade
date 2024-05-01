#include "Framework.h"

Boss::Boss(int key, float speed, bool isBubble, int hp, Type type) 
	: Monster(key, speed, isBubble, hp, true), type(type)
{
	actions[IDLE] = new BossIdle(this, key, 9);
	actions[MOVE] = new MonsterMove(this, key, speed, 6);
	actions[HIT] = new BossHit(this, key, 5 );
	actions[DIE] = new MonsterDie(this, key, 12 );
	actions[ATTACK] = new BossAttack(this, key , 20);
	actions[BUBBLE] = new MonsterBubble(this, key , 8);

	curType = IDLE;
	curState = curType;

	SetColliderSize(Tile::TILE_SIZE * 4);
	collider->Translate({0,-Tile::TILE_SIZE });

	maxHp = hp;

	hpBar = new ProgressBar(PATH + to_wstring(key) + L"/HpBarFront.png", PATH + to_wstring(key) + L"/HpBarBack.png");
	hpBar->SetAmount((float)hp / maxHp);
	hpBar->SetParent(this);
	hpBar->Translate({ 0, 60.0f });

	RenderManager::Get()->Add("HpBar", hpBar);
}

Boss::~Boss()
{
	delete hpBar;
}

void Boss::Update()
{
	Monster::Update();

	hpBar->SetLocalScale(GetLocalScale());
	hpBar->UpdateWorld();

	Attack();

	BubbleManager::Get()->CollisionBoss(this);
}

void Boss::Render()
{
	Monster::Render();

	hpBar->SetAmount((float)hp / maxHp);
}

void Boss::Attack()
{
	if (curState == BUBBLE || curState == DIE) return;

	playTime += DELTA;

	if (playTime > attackTime && hp <= maxHp * 0.5f)
	{
		playTime -= attackTime;
		SetAction(ATTACK);
	}
}

void Boss::Hit(Collider* collider)
{
	Monster::Hit(collider);
	if (hp <= maxHp * 0.5f)
	{
		curType = MOVE;
		curState = curType;
	}
}
