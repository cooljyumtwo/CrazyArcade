#pragma once

class WheelSkill : public Skill
{
public:
    WheelSkill(Transform* owner);
    ~WheelSkill();

    virtual void Update() override;
    virtual void Render() override;

    void LevelUp() override;

private:
    vector<GameObject*> wheels;

    Transform* wheelParent;
};