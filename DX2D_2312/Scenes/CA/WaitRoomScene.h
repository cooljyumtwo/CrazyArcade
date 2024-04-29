#pragma once

class WaitRoomScene : public Scene
{
public:
    WaitRoomScene();
    ~WaitRoomScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:

};