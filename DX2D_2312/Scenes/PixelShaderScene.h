#pragma once

class PixelShaderScene : public Scene
{
public:
    PixelShaderScene();
    ~PixelShaderScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Quad* quad;

    IntValueBuffer* valueBuffer;
    FloatValueBuffer* outlineBuffer;
    ColorBuffer* outlineColorBuffer;

    Texture* secondMap;
};