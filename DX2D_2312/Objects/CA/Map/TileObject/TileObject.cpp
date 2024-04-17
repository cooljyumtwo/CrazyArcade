#include "Framework.h"

TileObject::TileObject() : Quad()
{
	SetActive(false);

	img = new Quad();
	img->SetParent(this);
}

TileObject::~TileObject()
{
	delete img;
}

void TileObject::Update()
{
	if (!IsActive()) return;
}

void TileObject::Render()
{
	if (!IsActive()) return;

	Quad::Render();
}

void TileObject::Spawn(const Vector2& pos, const wstring textureFile)
{
	if (IsActive()) return;

	this->SetActive(true);

	SetTexture(textureFile);

	SetLocalPosition(pos);
	Translate(Vector2::Up() * (GetSize().y - 40.0f) * 0.5f);
	UpdateWorld();
}

void TileObject::AddAction(wstring file, int frameX, int frameY)
{
	//Action* action = new Action();

	//wstring actionFile = ToWString("ResourcesCA/Textures/Character/Bazzi/Run") + L".png";

	//action->LoadClip(file, frameX, frameY, true);
	//action->Start();
}
