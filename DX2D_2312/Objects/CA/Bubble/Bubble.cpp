#include "Framework.h"

Bubble::Bubble()
{
	SetActive(false);
	CreatActions();
	SetColliderSize({ Tile::TILE_SIZE + OFFSET_SIZE, Tile::TILE_SIZE + OFFSET_SIZE });
}

Bubble::~Bubble()
{
	for (auto& pair : actions)
		delete pair.second;
	actions.clear();
}

void Bubble::Update()
{
	if (!this->IsActive()) return;
	
	Push();

	playTime += DELTA;

	if (playTime > MAX_PLAY_TIME)
	{
		playTime -= MAX_PLAY_TIME;
		SetAction(POP);
	}

	UpdateWorld();
	collider->UpdateWorld();
	actions[curState]->Update();

	if (isTarget && !GetCollider()->IsCollision(target->GetCollider()))
		SetIsTarget(false);
}

void Bubble::Render()
{
	if (!this->IsActive()) return;

	collider->Render();
	actions[curState]->Render();
}

void Bubble::CreatActions()
{
	Action* action = new Action();
	action->LoadClip(ToWString(PATH) + L"Stand.png", 3, 1, true, 1.4f);
	actions[STAND] = action;

	action = new Action();
	action->LoadClip(ToWString(PATH) + L"Pop.png", 6, 1, false, 2.0f);
	action->GetClip(0)->SetEvent([this]() {
		TileManager::Get()->SetIdxBgTileType(posTileIdx, Tile::BASIC);
		Tile* tile = TileManager::Get()->GetNearPosTileState(this->GetGlobalPosition());
		if (tile)
			posTileIdx = tile->GetCurIdx();
		TileManager::Get()->SetIdxBgTileType(posTileIdx,Tile::ATTACK);
		BubbleManager::Get()->SpawnWaves(this->GetGlobalPosition(), power);
		},3);

	action->GetClip(0)->SetEvent([this]() {
		if (target)
			target->MinusBubbleCurCnt();

		TileManager::Get()->SetIdxBgTileType(posTileIdx,Tile::BASIC);
		SetActive(false);
		});
	actions[POP] = action;
	
}

void Bubble::Spawn(const Vector2& pos, int power, Character* target)
{
	isTarget = true;
	isPush = false;

	UpdateWorld();
	collider->UpdateWorld();

	Tile* tile = TileManager::Get()->GetNearPosTileState(pos);

	if (!tile) return;
	if (tile->GetType() == Tile::OBSTACLE) return;

	if (!Audio::Get()->IsPlaySound("BubbleAdd"))
	{
		Audio::Get()->Play("BubbleAdd");
	}

	SetActive(true);
	SetAction(STAND);
	
	this->power = power;
	this->SetGlobalPosition(tile->GetGlobalPosition());
	this->target = target;

	posTileIdx = tile->GetCurIdx();

	tile->SetType(Tile::OBSTACLE);

	if(target)
		target->PlusBubbleCurCnt();
}

void Bubble::Pop()
{
	TileManager::Get()->SetIdxBgTileType(posTileIdx, Tile::BASIC);
	SetAction(POP);
	playTime = 0.0f;
}

void Bubble::Push()
{
	if (curState == POP) return;
	if (pushDirection == NONE) return;
	if (!isPush) return;
	TileManager::Get()->PushGameObject(this);
		switch (pushDirection)
		{
		case Bubble::R:
			if (TileManager::Get()->GetMapsize("Right") - Tile::TILE_SIZE > GetGlobalPosition().x)
				Translate(Vector2::Right() * 5.0f);
			break;
		case Bubble::L:
			if (TileManager::Get()->GetMapsize("Left") < GetGlobalPosition().x)
				Translate(Vector2::Left() * 5.0f);
			break;
		case Bubble::U:
			if (TileManager::Get()->GetMapsize("Up") > GetGlobalPosition().y)
				Translate(Vector2::Up() * 5.0f);
			break;
		case Bubble::D:
			if (TileManager::Get()->GetMapsize("Down") + Tile::TILE_SIZE < GetGlobalPosition().y)
				Translate(Vector2::Down() * 5.0f); //°íÄ¡±â
			break;
		default:
			break;
		}
}

void Bubble::SetAction(int state)
{
	if (curState == state) return;

	curState = (State)state;
	actions[curState]->Start();
}
