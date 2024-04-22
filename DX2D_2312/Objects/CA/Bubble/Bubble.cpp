#include "Framework.h"

Bubble::Bubble()
{
	SetActive(false);

	CreatActions();

	collider = new RectCollider({ Tile::TILE_SIZE-10.0f, Tile::TILE_SIZE - 10.0f });
	collider->SetParent(this);

}

Bubble::~Bubble()
{
	delete collider;
}

void Bubble::Update()
{

	if (!this->IsActive()) return;

	playTime += DELTA;
	if (playTime > MAX_PLAY_TIME)
	{
		playTime -= MAX_PLAY_TIME;
		SetAction(POP);
	}

	UpdateWorld();
	collider->UpdateWorld();
	actions[curState]->Update();
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
		TileManager::Get()->SetIdxBgTileType(posTileIdx,Tile::ATTACK);
		BubbleManager::Get()->SpawnWaves(this->GetGlobalPosition(), 1);
		},1);

	action->GetClip(0)->SetEvent([this]() {
		TileManager::Get()->SetIdxBgTileType(posTileIdx,Tile::BASIC);
		SetActive(false);
		});
	actions[POP] = action;
	
}

void Bubble::Spawn(const Vector2& pos, int speed)
{
	UpdateWorld();
	collider->UpdateWorld();

	Tile* tile = TileManager::Get()->GetNearPosTileState(pos);

	if (!tile) return;

	SetActive(true);
	SetAction(STAND);
	this->power = power;
	this->SetGlobalPosition(tile->GetGlobalPosition());

	posTileIdx = tile->GetCurIdx();
}

float Bubble::GetDepth()
{
	return collider->Bottom();
}

void Bubble::SetAction(int state)
{
	if (curState == state) return;

	curState = (State)state;
	actions[curState]->Start();
}
