#pragma once

class InstancingScene : public Scene
{
private:
    const UINT SIZE = 1000;

public:
    InstancingScene();
    ~InstancingScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Quad* quad;

    vector<Matrix> instances;
    VertexBuffer* instanceBuffer;
};