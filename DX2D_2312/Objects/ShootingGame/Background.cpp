#include "Framework.h"

Background::Background(wstring textureFile) : textureFile(textureFile)
{
    texture = Texture::Add(textureFile);
    size = texture->GetSize();

    CreateBG();
}

Background::~Background()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            delete bgs[i][j];
        }
    }
}

void Background::Update()
{
    if (target->GetGlobalPosition().x < center->GetGlobalPosition().x - size.x * 0.5f)
        Move(Direction::LEFT);
    
    if (target->GetGlobalPosition().x > center->GetGlobalPosition().x + size.x * 0.5f)
        Move(Direction::RIGHT);

    if (target->GetGlobalPosition().y < center->GetGlobalPosition().y - size.y * 0.5f)
        Move(Direction::DOWN);

    if (target->GetGlobalPosition().y > center->GetGlobalPosition().y + size.y * 0.5f)
        Move(Direction::UP);
}

void Background::CreateBG()
{
    for (int y = -1 ; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            Vector2 offset = { (float)x , (float)y };
            Vector2 pos = CENTER + offset * size;

            Quad* bg = new Quad(textureFile);
            bg->SetLocalPosition(pos);
        //    bg->SetDepth(-10);

            bgs[y + 1][x + 1] = bg;
        }
    }

    center = bgs[1][1];
}

//void Background::Move(Direction direction)
//{
//    for (int y = 0; y < 3; y++)
//    {
//        for (int x = 0; x < 3; x++)
//        {
//            switch (direction)
//            {
//            case GameMath::Direction::UP:
//                bgs[y][x]->Translate(Vector2::Up() * size.y);
//                break;
//            case GameMath::Direction::DOWN:
//                bgs[y][x]->Translate(Vector2::Down() * size.y);
//                break;
//            case GameMath::Direction::LEFT:
//                bgs[y][x]->Translate(Vector2::Left() * size.x);
//                break;
//            case GameMath::Direction::RIGHT:
//                bgs[y][x]->Translate(Vector2::Right() * size.x);
//                break;
//            }
//        }
//    }
//}

void Background::Move(Direction direction)
{
    FOR(3)
    {
        switch (direction)
        {
        case GameMath::Direction::UP:
            bgs[0][i]->Translate(Vector2::Up() * size.y * 3);

            swap(bgs[2][i], bgs[0][i]);
            swap(bgs[1][i], bgs[0][i]);
            break;
        case GameMath::Direction::DOWN:
            bgs[2][i]->Translate(Vector2::Down() * size.y * 3);            

            swap(bgs[2][i], bgs[0][i]);
            swap(bgs[1][i], bgs[2][i]);
            break;
        case GameMath::Direction::LEFT:
            bgs[i][2]->Translate(Vector2::Left() * size.x * 3);

            swap(bgs[i][2], bgs[i][0]);
            swap(bgs[i][1], bgs[i][2]);
            break;
        case GameMath::Direction::RIGHT:
            bgs[i][0]->Translate(Vector2::Right() * size.x * 3);

            swap(bgs[i][2], bgs[i][0]);
            swap(bgs[i][1], bgs[i][0]);
            break;        
        default:
            break;
        }
    }

    center = bgs[1][1];
}
