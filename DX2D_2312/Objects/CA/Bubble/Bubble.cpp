#include "Framework.h"

Bubble::Bubble()
{
	SetActive(false);
	CreatActions();
	SetColliderSize({ Tile::TILE_SIZE, Tile::TILE_SIZE}, 1.0f);
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
	action->LoadClip(ToWString(PATH) + L"Stand.png", 3, 1, true, 2.5f);
	actions[STAND] = action;

	action = new Action();
	action->LoadClip(ToWString(PATH) + L"Pop.png", 6, 1, false, 5.0f);
	action->GetClip(0)->SetEvent([this]() {
		TileManager::Get()->SetIdxBgTileType(posTileIdx, Tile::BASIC);
		Tile* tile = TileManager::Get()->GetNearPosTileState(this->GetGlobalPosition());

		if (tile)
			posTileIdx = tile->GetCurIdx();

		TileManager::Get()->SetIdxBgTileType(posTileIdx,Tile::ATTACK);
		BubbleManager::Get()->SpawnWaves(this->GetGlobalPosition(), power);

		},4);

	action->GetClip(0)->SetEvent([this]() {
		if (target)
			target->MinusBubbleCurCnt();

		if (!Audio::Get()->IsPlaySound("BubblePop"))
		{
			Audio::Get()->Play("BubblePop", 1.5f);
		}

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

	if (!tile || tile->GetType() == Tile::OBSTACLE) return;

	if (!Audio::Get()->IsPlaySound("BubbleAdd"))
		Audio::Get()->Play("BubbleAdd", 1.5f);

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

void Bubble::SetIsPush(bool isPush)
{
	if (this->isPush != isPush)
	{
		if (this->isPush)
		{
			SetTileType(Tile::OBSTACLE);
		}
		else 
		{
			SetTileType(Tile::BASIC);
		}
	}

	this->isPush = isPush; 
}

void Bubble::Push()
{
	if (curState == POP || pushDirection == NONE || !isPush) return;

	if (TileManager::Get()->PushGameObject(this))
		SetIsPush(false);

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

void Bubble::SetTileType(Tile::Type type)
{
	Tile* tile = TileManager::Get()->GetNearPosTileState(this->GetGlobalPosition());
	tile->SetType(type);
}

void Bubble::SetAction(int state)
{
	if (curState == state) return;

	curState = (State)state;
	actions[curState]->Start();
}
