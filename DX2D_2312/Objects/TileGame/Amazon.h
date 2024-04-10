#pragma once

class Amazon : public GameObject
{
private:
    enum Compass
    {
        NONE,
        N = 1,        
        E = 2,
        S = 4,
        W = 8,
        SE = 6,
        NE = 3,        
        SW = 12,
        NW = 9

    };

public:
    Amazon();
    ~Amazon();

    void Update() override;
    void Render() override;

    void SetPath(vector<Vector2> path) { this->path = path; }
private:
    void AddAction(string file, int frameX, int frameY);
    void KeyControl();
    void MouseControl();
    void SetAnimState();
    void Move();

    void SetState(int state, int compass);

private:
    vector<Action*> actions;
    Compass compass = NONE;

    float speed = 100.0f;
    int curState = 0;
    Vector2 velocity;    

    vector<Vector2> path;
};