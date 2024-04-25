#pragma once

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

    void Start() override;


private:
    EditTileMap* tileMap;
    Player* player;
};