#include "Framework.h"

MapSelectButton::MapSelectButton(wstring textureFile, int key)
	:Button(textureFile), key(key)
{
	font = new ImageFont( L"ResourcesCA/Textures/UI/ResultNumber/");
}

MapSelectButton::~MapSelectButton()
{
}

void MapSelectButton::Update()
{
	Button::Update();
	font->UpdateWorld();
}

void MapSelectButton::Render()
{
	Button::Render();
	font->Render();
	font->RenderUI();
}

void MapSelectButton::SetFont(int num)
{
	font->SetParent(this);
	font->SetLocalPosition(this->GetLocalPosition());
	font->Translate({-30.0f, 0.0f});
	font->UpdateWorld();
	font->SetAligned(ImageFont::AlignedType::R);
	font->SetValue((UINT)num);
}
