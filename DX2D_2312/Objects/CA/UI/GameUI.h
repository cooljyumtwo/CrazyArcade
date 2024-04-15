#pragma once

class GameUI : public UI
{
public:
    GameUI();
    ~GameUI();

    void Update() override;
    void PreRender() override;
    void Render() override;
    void PostRender() override;


private:
    Quad* BG;
};