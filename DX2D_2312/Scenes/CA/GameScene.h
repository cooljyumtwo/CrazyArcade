#pragma once

class GameScene : public Scene
{
private:
    const string AUDIO_PATH = "ResourcesCA/Audio/";

public:
    GameScene();
    ~GameScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

    void Start() override;
    void End() override;

private:
    EditTileMap* tileMap;
    Player* player;
};