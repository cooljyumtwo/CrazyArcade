#include "Framework.h"

Waves::Waves()
{
	SetActive(false);

	CreateWaves();
}

Waves::~Waves()
{
	for (auto it = waves.begin(); it != waves.end(); ++it) 
	{
		auto& waveList = it->second;
		for (Wave* wave : waveList) 
			delete wave;
	}
}

void Waves::Update()
{
	if (!IsActive()) return;

	for (auto it = waves.begin(); it != waves.end(); ++it) 
	{
		auto& waveList = it->second;
		for (Wave* wave : waveList) 
			wave->Update();
	}

	ClearWaves();

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

			if (!tile) continue;

			//물풍선 파도를 생성할때 상하좌우 확인하는 for문
			//파도가 생성할 해당 Pos의 Type이 OBSTACLE일 경우
			if (tile->GetType() == Tile::OBSTACLE)
			{
				BasicTile* basicTile = (BasicTile*)tile;
				ObstacleTile* obstacleTile = (ObstacleTile*)basicTile->GetObstacleTile();
				
				if (obstacleTile == nullptr) return;

				// 장애물 타일이 존재하고 활성화되어 있다면
				if (obstacleTile != nullptr && obstacleTile->IsActive())
				{
					// 장애물 타일을 비활성화 상태로 설정
					obstacleTile->Deactivate();
				}

				// 기본 타일의 장애물 타일을 제거하고 기본 타일로 설정
				basicTile->SetObstacleTile(nullptr);
				basicTile->SetType(Tile::BASIC);
				break;
			}


			if (i == power - 1)
				waveList[i]->Spawn(pos, waveType, Wave::END);
			else
				waveList[i]->Spawn(pos, waveType, Wave::START);

			waveList[i]->SetPosTileIdx(tile->GetCurIdx());

		}
	}
}

void Waves::ClearWaves()
{
	int count = 0;
	int wavesSize = 0;
	for (auto it = waves.begin(); it != waves.end(); ++it) 
	{
		auto& waveList = it->second;
		for (Wave* wave : waveList) 
		{
			wavesSize++;
			if (!wave->IsActive()) count++;
		}

	}
	if (count == wavesSize)
		SetActive(false);
	else
		SetActive(true);
}
