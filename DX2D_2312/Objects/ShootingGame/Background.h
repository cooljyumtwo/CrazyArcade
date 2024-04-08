#pragma once

class Background
{
public:
    Background(wstring textureFile);
    ~Background();

    void Update();

    void SetTarget(Transform* target) { this->target = target; }

private:
    void CreateBG();
    void Move(Direction direction);

private:
    Quad* bgs[3][3];
    Quad* center;

    Texture* texture;
    wstring textureFile;

    Vector2 size;

    Transform* target;
};