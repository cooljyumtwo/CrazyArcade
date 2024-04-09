#pragma once

class StageScene : public Scene
{
public:
    StageScene();
    ~StageScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    EditTileMap* tileMap;
};