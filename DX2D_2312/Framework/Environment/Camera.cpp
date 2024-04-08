#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    viewBuffer = new MatrixBuffer();
    viewBuffer->SetVS(1);
}

Camera::~Camera()
{
    delete viewBuffer;
}

void Camera::Update()
{
    if (target)
        FollowMode();
    else
        FreeMode();

    SetView();
}

void Camera::RenderUI()
{
    if (ImGui::TreeNode("Camera Option"))
    {
        ImGui::DragFloat("Speed", &speed);
        ImGui::DragFloat2("Offset", (float*)&targetOffset);

        ImGui::TreePop();
    }    
}

void Camera::SetView()
{
    UpdateWorld();

    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view);
    viewBuffer->SetVS(1);
}

bool Camera::ContainFrustum(Vector2 pos, Vector2 size)
{
    Vector2 leftBottom = pos - size * 0.5f;
    Vector2 rightTop = pos + size * 0.5f;

    if (localPosition.x < rightTop.x && localPosition.x + SCREEN_WIDTH > leftBottom.x)
    {
        if (localPosition.y < rightTop.y && localPosition.y + SCREEN_HEIGHT > leftBottom.y)
            return true;
    }

    return false;
}

bool Camera::ContainFrustum(Quad* quad)
{    
    return ContainFrustum(quad->GetGlobalPosition(), quad->GetSize());
}

Vector2 Camera::ScreenToWorld(const Vector2& screenPos)
{
    return screenPos * world;
}

Vector2 Camera::WorldToScreen(const Vector2& worldPos)
{
    return worldPos * view;
}

void Camera::FreeMode()
{
    if (KEY->Press(VK_RBUTTON))
    {
        if (KEY->Press('W'))
            Translate(Vector2::Up() * speed * DELTA);
        if (KEY->Press('S'))
            Translate(Vector2::Down() * speed * DELTA);
        if (KEY->Press('A'))
            Translate(Vector2::Left() * speed * DELTA);
        if (KEY->Press('D'))
            Translate(Vector2::Right() * speed * DELTA);
    }

    FixPosition(localPosition);
}

void Camera::FollowMode()
{
    Vector2 targetPos = target->GetGlobalPosition() - targetOffset;

    FixPosition(targetPos);

    localPosition = Lerp(localPosition, targetPos, speed * DELTA);
}

void Camera::FixPosition(Vector2& pos)
{
    if (!isFix) return;

    if (pos.x < leftBottom.x)
        pos.x = leftBottom.x;

    if (pos.x > rightTop.x - SCREEN_WIDTH)
        pos.x = rightTop.x - SCREEN_WIDTH;

    if (pos.y < leftBottom.y)
        pos.y = leftBottom.y;

    if (pos.y > rightTop.y - SCREEN_HEIGHT)
        pos.y = rightTop.y - SCREEN_HEIGHT;
}
