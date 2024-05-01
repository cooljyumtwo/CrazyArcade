#pragma once

class Button : public Quad
{
protected:
    enum State
    {
        NORMAL, OVER, DOWN
    };

    const Float4 NORMAL_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
    const Float4 OVER_COLOR = { 0.9f, 0.9f, 0.9f, 1.0f };
    const Float4 DOWN_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };

public:
    Button(wstring textureFile = L"Resources/Textures/UI/Button.png");
    ~Button();

    void Update() override;
    void Render() override;

    void UpdateWorld() override;

    void SetEvent(Event event) { 
        clickEvent = event; 
    }
    void SetIntEvent(IntParamEvent event, int param)
    { clickIntParamEvent = event, intParam = param; }
    void SetObjectEvent(ObjectParamEvent event, void* param)
    { clickObjectParamEvent = event, objectParam = param; }

    void SetText(string text) { this->text = text; }
    void SetTextData(string color, string style)
    {
        textColor = color, textStyle = style;
    }

protected:
    void ClickEvent();

protected:

    Event clickEvent = nullptr;
    IntParamEvent clickIntParamEvent = nullptr;
    ObjectParamEvent clickObjectParamEvent = nullptr;

    int intParam = 0;
    void* objectParam = nullptr;

    State state = NORMAL;
    bool isDownCheck = false;

    string text;

    string textColor = "Black";
    string textStyle = "Button";
};