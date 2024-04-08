#pragma once

class FloorManager : public Singleton<FloorManager>
{
private:
    friend class Singleton;

    FloorManager();
    ~FloorManager();

public:
    void Update();
    void Render();

    void Add(const Vector2& pos, wstring textureFile);
    void Remove();

    void Load();

    RectCollider* Collision(Collider* collider);

    Quad* GetBG() { return background; }    
private:
    void Save();        

    void SaveBG();
    void LoadBG();

private:
    Quad* background;
    vector<Floor*> floors;
};