#include "Framework.h"

Waves::Waves()
{
	SetActive(false);
	CreateWaves();
}

Waves::~Waves()
{
	for (auto it = waves.begin(); it != waves.end(); ++it) {
		auto& waveList = it->second;
		for (Wave* wave : waveList) {
			delete wave;
		}
	}
}

void Waves::Update()
{
	if (!IsActive()) return;

	for (auto it = waves.begin(); it != waves.end(); ++it) {
		auto& waveList = it->second;
		for (Wave* wave : waveList) {
				wave->Update();
		}
	}

	UpdateWorld();
}

void Waves::Render()
{
}

void Waves::CreateWaves()
{
	CreateDirectionWaves(L);
	CreateDirectionWaves(R);
	CreateDirectionWaves(U);
	CreateDirectionWaves(D);
}

void Waves::CreateDirectionWaves(Direction direction)
{
	Vector2 velocity = { 0, 0 };

	switch (direction)
	{
	case Waves::R:
		velocity.x = 1.0f;
		break;
	case Waves::L:
		velocity.x = -1.0f;
		break;
	case Waves::U:
		velocity.y = 1.0f;
		break;
	case Waves::D:
		velocity.y = -1.0f;
		break;
	default:
		break;
	}

	FOR(MAX_POWER)
	{
		Wave* wave = new Wave();
		wave->SetParent(this);
		wave->SetLocalPosition(velocity * (i+1) * Tile::TILE_SIZE);
		wave->UpdateWorld();
		waves[direction].push_back(wave);
		RenderManager::Get()->Add("GameObject", wave);
	}
}

void Waves::Spawn(const Vector2& pos, int power)
{
	SetActive(true);
	SetGlobalPosition(pos);

	Wave::Direction waveType = Wave::R;

	for (auto it = waves.begin(); it != waves.end(); ++it) {
		auto& direction = it->first;
		auto& waveList = it->second;
		for (int i = 0; i < power; i++)
		{
			switch (direction) {
			case R:
				waveType = Wave::R;
				break;
			case L:
				waveType = Wave::L;
				break;
			case U:
				waveType = Wave::U;
				break;
			case D:
				waveType = Wave::D;
				break;
			}

			Tile* tile = TileManager::Get()->GetNearPosTileState(GetGlobalPosition() + waveList[i]->GetLocalPosition());

			if (tile->GetType() == Tile::OBSTACLE)
			{
				BasicTile* basicTile = (BasicTile*)tile;

				ObstacleTile* obstacleTile = (ObstacleTile*)basicTile->GetObstacleTile();
				if (obstacleTile != nullptr && obstacleTile->IsActive())
					obstacleTile->End();

				basicTile->SetObstacleTile(nullptr);
				basicTile->SetType(Tile::BASIC);

				ItemManager::Get()->Spawn(tile->GetGlobalPosition());
				break;
			}

			else 
				tile->SetType(Tile::ATTACK);

			if (i == power-1)
				waveList[i]->Spawn(pos, waveType, Wave::END);
			else
				waveList[i]->Spawn(pos, waveType, Wave::START);

			waveList[i]->SetPosTileIdx(tile->GetCurIdx());

		}

		if (next(it) == waves.end())
			waveList[0]->GetAction()->GetCurClip()->SetEvent([this]() { this->End(); }, 1);
	}
}

void Waves::End()
{
	//TileManager::Get()->PopObjTile();
}

void Waves::ClearWaves()
{
	for (auto it = waves.begin(); it != waves.end(); ++it) 
	{
		auto& waveList = it->second;
		for (Wave* wave : waveList) {
			wave->SetActive(false);
		}
	}
}
