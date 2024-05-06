#pragma once

class Item : public Quad
{
private:
    wstring PATH = L"ResourcesCA/Textures/Item/";
    const float MAX_PLAY_TIME = 0.1f;

public:
    enum Type
    {
        B_POWER, B_CNTUP, U_SPEED, B_PUSH,
        B_NEEDLE = 10
    };

public:
    Item();

    void Update() override;
    void Render() override;

    void Spawn(const Vector2& pos, ItemData data);
    void SetData(ItemData data);

    void AddCount(int value) { count += value; }

    ItemData GetData() { return data; }
    bool IsField() { return isField; }  
    int GetCount() { return count; }

    void SetInven() { isField = false; }

    void Play();

private:
    void SetLevelColor();

private:
    Quad* shadow;
    ItemData data;

    bool isField = false;    

    int count = 1;

    float playTime = 0.0f;

    OutlineBuffer* outlineBuffer;
};