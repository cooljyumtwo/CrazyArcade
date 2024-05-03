#include "Framework.h"
#include "Boss.h"

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
	for (auto action : actions)
		delete action.second;

	RenderManager::Get()->Remove("HpBar", hpBar);
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
	if (curState == BUBBLE || curState == DIE || curState == HIT) return;

	playTime += DELTA;

	if (playTime > attackTime)
	{
		playTime -= attackTime;
		SetAction(ATTACK);
	}
}

void Boss::CheckTileHit()
{
	if (curState == DIE || curState == HIT) return;
	Vector2 curPos = GetCollider()->GetGlobalPosition();
	vector<Vector2> checkPos;

	vector<Vector2> offsets = {
		Vector2{-1, -1}, Vector2{-1, 0}, Vector2{-1, 1},
		Vector2{0, -1}, Vector2{0, 0}, Vector2{0, 1},
		Vector2{1, -1}, Vector2{1, 0}, Vector2{1, 1}
	};

	for (const auto& offset : offsets) {
		checkPos.push_back(curPos + offset * Tile::TILE_SIZE);
	}

	for (Vector2 pos : checkPos)
	{
		Tile* tile = TileManager::Get()->GetNearPosTileState(pos);

		if (!tile) return;

		if (tile->GetType() == Tile::ATTACK)
		{
			Hit(tile->GetCollider());
		}
	}
}

void Boss::Hit(Collider* collider)
{
	if (curState == DIE || curState == BUBBLE || curState == HIT) return;

	Monster::Hit(collider);
	CheckMode();
}

void Boss::CheckMode()
{
	if (hp <= maxHp * 0.5f)
	{
		modeState = ANGRY;
		curType = MOVE;
		attackTime = ANGRY_STAY_TIME;
	}
	else
		modeState = NORMAL;
}
