#include "Framework.h"

Boss::Boss(int key, float speed, bool isBubble, int hp, Type type) 
	: Monster(key, speed, isBubble, hp), type(type)
{
	actions[MOVE] = new MonsterMove(this, key, speed, 6);
	actions[HIT] = new BossHit(this, key, 5 );
	actions[DIE] = new MonsterDie(this, key, 12 );
	actions[ATTACK] = new BossAttack(this, key , 20);

	SetColliderSize(Tile::TILE_SIZE * 4);
	collider->Translate({0,-Tile::TILE_SIZE });

	maxHp = hp;

	hpBar = new ProgressBar(PATH + to_wstring(key) + L"/HpBarFront.png", PATH + to_wstring(key) + L"/HpBarBack.png");
	hpBar->SetAmount((float)hp / maxHp);
	hpBar->SetParent(this);
	hpBar->Translate({ 0, 60.0f });
}

Boss::~Boss()
{
}

void Boss::Update()
{
	Monster::Update();

	playTime += DELTA;
	if (playTime > attackTime)
	{
		playTime -= attackTime;
		SetAction(ATTACK);
	}

	hpBar->SetLocalScale(GetLocalScale());
	hpBar->UpdateWorld();
}

void Boss::PostRender()
{
	hpBar->Render();
	hpBar->SetAmount((float)hp / maxHp);
}