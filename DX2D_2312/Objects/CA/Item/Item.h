#pragma once

class Item : public Quad
{
public:
    Item();

    void Update() override;
    

    void Spawn(const Vector2& pos, ItemData data);
    void SetData(ItemData data);

    void AddCount(int value) { count += value; }

    ItemData GetData() { return data; }
    bool IsField() { return isField; }  
    int GetCount() { return count; }

    void SetInven() { isField = false; }

    RectCollider* GetCollider() { return collider; }

private:
    void SetLevelColor();

private:
    ItemData data;

    RectCollider* collider;

    bool isField = false;    

    int count = 1;
};