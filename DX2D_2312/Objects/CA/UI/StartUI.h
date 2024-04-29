#pragma once

class StartUI : public UI
{
    const float MAX_FRAME_TIME = 0.1f;
    const float MAX_FRAME_COUNT = 13;
    const wstring PATH_START = PATH + L"/Start/";
    
public:
    StartUI();
    ~StartUI();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;

    void CreateUIs();
    void CreateBuffers();

    void PlayIntro();

private:
    Quad* bg;
    Button* startBtn;

    IntValueBuffer* valueBuffer;

    FloatValueBuffer* outlineBuffer;
    Texture* secondMap;

    float frameTime = 0.0f;
    int count = 0;
    bool isEndIntro = false;

    vector<Texture*> bgTexs;
    vector<wstring> introBgs = { L"IntroLogo.png", L"IntroTitle.png", L"loginBG.png" };

};