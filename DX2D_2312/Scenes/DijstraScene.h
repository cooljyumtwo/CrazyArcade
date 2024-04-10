#pragma once

class DijstraScene : public Scene
{
public:
    DijstraScene();
    ~DijstraScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Amazon* amazon;

    Dijkstra* dijkstra;
};