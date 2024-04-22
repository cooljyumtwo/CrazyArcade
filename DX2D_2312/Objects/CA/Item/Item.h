#pragma once

class Item : public Button
{
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

private:
    void SetLevelColor();

private:
    ItemData data;

    bool isField = false;    

    int count = 1;
};