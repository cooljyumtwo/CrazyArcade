#pragma once

class MapEditScene : public Scene
{
public:
    MapEditScene();
    ~MapEditScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    EditTileMap* tileMap;
    Player* player;
    Quad* quad;
    TileObject* t;
};