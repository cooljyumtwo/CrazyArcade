#pragma once

class AnimationScene : public Scene
{
public:
    AnimationScene();
    ~AnimationScene();
        
    void Update() override;

    void PreRender() override;
    void Render() override;
    void PostRender() override;

private:
    void CreateEffects();
    void CreateRenderTarget();

private:
    Cookie* cookie;

    RenderTarget* renderTarget;
    Quad* renderTexture;

    LightBuffer* lightBuffer;
};