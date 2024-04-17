#pragma once

class TileEditScene : public Scene
{
public:
    TileEditScene();
    ~TileEditScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    EditTileMap* tileMap;    
};