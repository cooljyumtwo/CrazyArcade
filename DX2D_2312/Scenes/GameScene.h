#pragma once

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    EditTileMap* tileMap;
    Player* player;
    Quad* quad; //test¿ë
};