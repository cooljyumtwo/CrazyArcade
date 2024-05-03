#pragma once

class WaitRoomScene : public Scene
{
public:
    WaitRoomScene();
    ~WaitRoomScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

    void Start() override;
    void End() override;

private:

};