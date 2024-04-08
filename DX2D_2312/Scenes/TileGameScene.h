#pragma once

class TileGameScene : public Scene
{
public:
    TileGameScene();
    ~TileGameScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Amazon* amazon;
};