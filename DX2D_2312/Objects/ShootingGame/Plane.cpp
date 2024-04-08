#include "Framework.h"

Plane::Plane() : Quad(L"Resources/Textures/Shooting/player.png")
{
	//colorBuffer->SetColor(Random(0.0f, 1.0f), Random(0.0f, 1.0f), Random(0.0f, 1.0f));

	//pivot = { -100, -100 };

	levelData = ShootingDataManager::Get()->GetLevelData(1);
	speed = levelData.speed;
	hp = levelData.hp;

	collider = new CircleCollider(70);
	collider->SetParent(this);

	cursor = new Quad(L"Resources/Textures/Shooting/cursor.png");
	cursor->SetParent(this);
	cursor->Translate(Vector2::Right() * 50.0f);

	skills.push_back(new BaseSkill(this));
	skills.push_back(new WheelSkill(this));	

	Observer::Get()->AddIntEvent("SkillLevelUp",
		bind(&Plane::SkillLevelUp, this, placeholders::_1));

	Observer::Get()->AddEvent("Save", bind(&Plane::SaveData, this));
	Observer::Get()->AddEvent("Load", bind(&Plane::LoadData, this));
}

Plane::~Plane()
{
	delete collider;
	delete cursor;	

	for (Skill* skill : skills)
		delete skill;
}

void Plane::Update()
{
	if (KEY->Press('W'))
		Translate(Vector2::Up() * speed * DELTA);
	if (KEY->Press('S'))
		Translate(Vector2::Down() * speed * DELTA);
	if (KEY->Press('A'))
		Translate(Vector2::Left() * speed * DELTA);
	if (KEY->Press('D'))
		Translate(Vector2::Right() * speed * DELTA);
	//
	//Vector2 direction = mousePos - localPosition;
	//localRotation.z = direction.Angle();

	//localPosition = mousePos;

	//if (KEY->Press('A'))
	//	localRotation.z += DELTA;
	//
	//if (KEY->Press('D'))
	//	localRotation.z -= DELTA;
	//
	//if (KEY->Press('W'))
	//	Translate(GetRight() * speed * DELTA);

	Collision();

	UpdateWorld();
	collider->UpdateWorld();

	cursor->UpdateWorld();
}

void Plane::Render()
{
	Quad::Render();
	collider->Render();
	cursor->Render();	
}

void Plane::PostRender()
{
	collider->RenderUI();

	string str = "HP : " + to_string(hp);
	ImGui::Text(str.c_str());
}

void Plane::Collision()
{
	Bullet* bullet = BulletManager::Get()->Collision("EnemyBullet", collider);

	if (bullet)
	{
		bullet->SetActive(false);
		hp--;
	}

	Item* item = ItemManager::Get()->Collision(collider);

	if (item)
	{
		ItemData data = item->GetData();

		if (data.type == 0)
		{
			item->SetActive(false);
			AddExp(data.value);
		}
		else
		{
			UIManager::Get()->GetInventory()->AddItem(item);
		}
	}
}

void Plane::AddExp(int value)
{
	levelData = ShootingDataManager::Get()->GetLevelData(level);
	LevelData nextLevelData = levelData;

	exp += value;	

	if (exp >= levelData.exp)
	{
		level++;
		speed = levelData.speed;
		exp -= levelData.exp;
		hp = levelData.hp;

		nextLevelData = ShootingDataManager::Get()->GetLevelData(level);

		UIManager::Get()->LevelUp();
	}

	UIManager::Get()->GetExpBar()->SetAmount((float)exp / nextLevelData.exp);
}

void Plane::SkillLevelUp(int index)
{
	skills[index]->LevelUp();
}

void Plane::SaveData()
{
	BinaryWriter* writer = new BinaryWriter("Resources/TextData/Shooting/Plane.data");

	writer->Int(level);
	writer->Int(hp);
	writer->Int(exp);
	writer->Int(skills[0]->GetData().key);
	writer->Int(skills[1]->GetData().key);

	delete writer;
}

void Plane::LoadData()
{
	BinaryReader* reader = new BinaryReader("Resources/TextData/Shooting/Plane.data");

	if (reader->IsFailed())
	{
		delete reader;
		return;
	}

	levelData = ShootingDataManager::Get()->GetLevelData(reader->Int());
	level = levelData.key;
	speed = levelData.speed;
	hp = reader->Int();
	exp = reader->Int();
	int baseSkill = reader->Int();
	int wheelSkill = reader->Int();

	skills[0]->SetData(baseSkill);

	if (wheelSkill > 201)
	{
		skills[1]->SetData(wheelSkill - 1);
		skills[1]->LevelUp();
	}	
}