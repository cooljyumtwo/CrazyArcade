#pragma once

class Floor : public Quad
{
public:
    Floor(wstring file);
    ~Floor();

    void Update() override;
    void Render() override;
};