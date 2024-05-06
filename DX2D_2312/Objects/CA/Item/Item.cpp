#include "Framework.h"

Item::Item()
{
    SetActive(false); 

    collider->SetParent(this);
    collider->GetColor()->SetColor(0.0f,1.0f,1.0f);

    shadow = new Quad(PATH + L"Shadow.png");
    shadow->SetParent(this);
    shadow->Translate(Vector2::Down() * Vector2{ 0, 20.0f});


    outlineBuffer = new OutlineBuffer();

}

void Item::Update()
{
    if (!IsActive()) return;

    shadow->UpdateWorld();
    UpdateWorld();
    collider->UpdateWorld();

    outlineBuffer->GetData().imageSize = this->GetSize();

    Play();
}

void Item::Render()
{
    if (!IsActive()) return;

    shadow->Render();
    Quad::Render();
    collider->Render();


}

void Item::Spawn(const Vector2& pos, ItemData data)
{
    SetActive(true);

    isField = true;

    this->data = data;

    wstring textureFile = PATH + data.textureFile;
    SetTexture(textureFile);
    collider->SetSize(size);

    SetLocalPosition(pos);

    UpdateWorld();
    collider->UpdateWorld();
}

void Item::SetData(ItemData data)
{
    SetActive(true);

    isField = false;    

    this->data = data;
    wstring textureFile = PATH + data.textureFile;
    SetTexture(textureFile);
    collider->SetSize(size);
}

void Item::Play()
{
    if (playTime <= MAX_PLAY_TIME)
    {
        Translate(Vector2::Up() * Vector2 { 0, 0.07f });
    }
    else if (playTime <= MAX_PLAY_TIME * 2 && playTime > MAX_PLAY_TIME)
    {
        Translate(Vector2::Down() * Vector2 { 0, 0.07f });
    }
    else if (playTime > MAX_PLAY_TIME * 2)
    {
        playTime -= MAX_PLAY_TIME * 2;

    }
    playTime += DELTA * 0.2f;
}

void Item::SetLevelColor()
{
    if (data.type == 0)
    {
        material->SetColor(1, 1, 1);
        return;
    }

    int level = data.key % 10;
    switch (level)
    {
    case 1:
        material->SetColor(1, 1, 1);
        break;
    case 2:
        material->SetColor(1, 1, 0);
        break;
    case 3:
        material->SetColor(0, 1, 0);
        break;
    case 4:
        material->SetColor(1, 0, 1);
        break;
    case 5:
        material->SetColor(1, 0, 0);
        break;
    default:
        break;
    }
}
