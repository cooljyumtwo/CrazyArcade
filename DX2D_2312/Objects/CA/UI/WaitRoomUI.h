#pragma once

class WaitRoomUI : public UI
{
    const float MAX_FRAME_TIME = 0.1f;
    const float MAX_FRAME_COUNT = 13;
    const wstring PATH_WAITROOM = PATH + L"/WaitRoom/";

public:
    WaitRoomUI();
    ~WaitRoomUI();

    void Start() override;

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;

    void CreateUIs();
    void CreateMapSelectWindow();
    void CreateBuffers();
    void CreateMapSelectLineBtns();
    void CreateFonts();

    void PlayIntro();

    void CloseWindow();

private:
    Quad* bg;
    Quad* mapSelectImg;
    Button* mapSelectBtn;
    Button* gameStartBtn;


    Quad* mapSelectWindow;
    Quad* mapSelectWindowMapImg;
    Quad* mapSelectWindowMapTxt;
    MapSelectButton* mapSelectLine;
    Button* acceptBtn;
    Button* cancelBtn;
    Button* mapEditBtn;
    Button* exitBtn;
    vector<MapSelectButton*> mapSelectLineBtns;

    IntValueBuffer* valueBuffer;

    FloatValueBuffer* outlineBuffer;
    Texture* secondMap;

    float frameTime = 0.0f;
    int count = 0;
    bool isEndIntro = false;


    ImageFont* font;
    float time = 0.0f;
    int selectKey;

    Vector2 fontpos;
public:
    static int stageKey;
};