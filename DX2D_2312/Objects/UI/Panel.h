#pragma once

class Panel : public Quad
{
public:
    Panel(wstring textureFile);
    ~Panel();

    virtual void Update() override;
    virtual void Render() override;

    Button* GetCloseBtn() { return closeBtn; }

private:
    void Drag();    

private:
    RectCollider* collider;

    Vector2 offset;    

    Button* closeBtn;
};