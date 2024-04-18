#include "Framework.h"

Bubble::Bubble()
{
	SetActive(false);

	CreatActions();

	collider = new RectCollider({ Tile::TILE_SIZE-10.0f, Tile::TILE_SIZE - 10.0f });
	collider->SetParent(this);

	wave = new Wave();
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
	wave->Update();
	
}

void Bubble::Render()
{
	if (!this->IsActive()) return;

	collider->Render();
	actions[curState]->Render();
	wave->Render();
}

void Bubble::CreatActions()
{
	Action* action = new Action();
	action->LoadClip(ToWString(PATH) + L"Stand.png", 3, 1, true);
	actions[STAND] = action;


	action = new Action();
	action->LoadClip(ToWString(PATH) + L"Pop.png", 6, 1, false);
	action->GetClip(0)->SetEvent([this]() {
		wave->Spawn(this->GetGlobalPosition(), 1);
		},0);
	action->GetClip(0)->SetEvent([this]() {
		SetActive(false);
		});
	actions[POP] = action;
	
}

void Bubble::Spawn(const Vector2& pos, int speed)
{
	UpdateWorld();
	collider->UpdateWorld();

	Tile* tile = TileManager::Get()->SetNearPosState(pos, Tile::OBSTACLE);

	if (!tile) return;

	SetActive(true);
	SetAction(STAND);
	this->power = power;
	this->SetGlobalPosition(tile->GetGlobalPosition());
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
