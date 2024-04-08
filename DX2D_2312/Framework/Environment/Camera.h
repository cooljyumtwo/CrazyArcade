#pragma once

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void RenderUI();

    void SetView();

    bool ContainFrustum(Vector2 pos, Vector2 size);
    bool ContainFrustum(class Quad* quad);

    Vector2 ScreenToWorld(const Vector2& screenPos);
    Vector2 WorldToScreen(const Vector2& worldPos);

    void SetLeftBottom(float x, float y) { leftBottom = { x, y }; }
    void SetLeftBottom(Vector2 pos) { leftBottom = pos; }
    void SetRightTop(float x, float y) { rightTop = { x, y }; }
    void SetRightTop(Vector2 pos) { rightTop = pos; }

    void SetTarget(Transform* target) { this->target = target; }
    void SetFix(bool isFix) { this->isFix = isFix; }

private:
    void FreeMode();
    void FollowMode();

    void FixPosition(Vector2& pos);

private:
    MatrixBuffer* viewBuffer;

    Matrix view;
    
    float speed = 300.0f;

    Vector2 leftBottom;
    Vector2 rightTop = { SCREEN_WIDTH, SCREEN_HEIGHT };

    Transform* target = nullptr;
    Vector2 targetOffset = { CENTER_X, CENTER_Y };

    bool isFix = true;
};