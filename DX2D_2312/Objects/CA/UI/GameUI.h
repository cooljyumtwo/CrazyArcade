#pragma once

class GameUI : public UI
{
public:
    enum State
    {
        READY, START, CLEAR, GAMEOVER
    };
    const wstring PATH_GAME = PATH + L"/Game/";

public:
    GameUI();
    ~GameUI();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;

    void SetGameTxt(State state);


private:
    Quad* BG;
    Quad* GameTxt;

    float frameTime = 0.0f;

    vector<Texture*> gameTxtTexs;
    vector<wstring> gameTxtStrs = { L"Ready.png", L"GameStart.png", L"Clear.png", L"GameOver.png"};
};