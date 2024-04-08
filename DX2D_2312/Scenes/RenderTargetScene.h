#pragma once

class RenderTargetScene : public Scene
{
public:
    RenderTargetScene();
    ~RenderTargetScene();

    void Update() override;

    void PreRender() override;
    void Render() override;
    void PostRender() override;

public:
    Cookie* cookie;

    RenderTarget* renderTarget;

    vector<Quad*> renderTextures;

    Camera* objectCamera;
};