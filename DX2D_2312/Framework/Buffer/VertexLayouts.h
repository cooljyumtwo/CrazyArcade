#pragma once

struct Vertex//정점 : 3차원 공간에서의 한 점
{
    float x, y, z;

    Vertex(float x, float y) : x(x), y(y), z(0)
    {
    }
};

struct VertexColor//정점 : 3차원 공간에서의 한 점
{
    float x, y, z;
    float r, g, b, a;

    VertexColor(float x, float y, float r, float g, float b)
        : x(x), y(y), z(0), r(r), g(g), b(b)
    {
    }
};

struct VertexUV
{
    Float3 pos;
    Float2 uv;
    
    VertexUV(float x = 0.0f, float y = 0.0f, float u = 0.0f, float v = 0.0f)
        : pos(x, y, 0.0f), uv(u, v)
    {
    }
};