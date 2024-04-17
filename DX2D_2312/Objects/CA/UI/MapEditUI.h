#pragma once

class MapEditUI : public UI
{
public:
    MapEditUI();
    ~MapEditUI();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;

private:
    Quad* BG;
    Button* exitBtn;
};