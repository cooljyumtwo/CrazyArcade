#pragma once

class StartScene : public Scene
{
private:
    const string AUDIO_PATH = "ResourcesCA/Audio/";

public:
    StartScene();
    ~StartScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

    void Start() override;
    void End() override;

    void CreateAudio();
private:

};