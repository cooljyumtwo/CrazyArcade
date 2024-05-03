#pragma once

class GameUI : public UI
{
    const float MAX_FRAME_TIME = 0.3f;
    const int MAX_COUNT = 5;
public:
    enum State
    {
        START, CLEAR, GAMEOVER
    };
    const wstring PATH_GAME = PATH + L"Game/";

public:
    GameUI();
    ~GameUI();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;

    void SetGameTxt(State state);
    void AniGameTxt();
    void AniBossTxt();

    void SetItemSlotImg(bool isItem, wstring imgStr = L"");

    void End() override;

private:
    Quad* bg;
    Quad* gameTxt;
    Quad* bossReadyTxt;

    Quad* itemSlotImg;

    State curState;

    Quad* resultWindow;
    Font* numMonster;

    float frameTime = 0.0f;
    int count = MAX_COUNT;

    Button* exitBtn;

    vector<Texture*> gameTxtTexs;
    vector<wstring> gameTxtStrs = { L"GameStart.png", L"Clear.png", L"GameOver.png"};

};