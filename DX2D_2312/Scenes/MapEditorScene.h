#pragma once

class MapEditorScene : public Scene
{
private:
    const int CELL_WIDTH = 124;
    const int CELL_HEIGHT = 20;

public:
    MapEditorScene();
    ~MapEditorScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    void EditBG();
    void EditTexture(Quad* quad, string key);      

private:    
    Quad* sampleTile;
};