#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	vertexShader = Shader::AddVS(L"Vertex.hlsl");
	pixelShader = Shader::AddPS(L"Pixel.hlsl");
        
    //UINT count = 100;
    ////Polygon : 정점 3개로 이루어진 3차원 상의 평면
    ////정점순서의 시계방향을 앞면으로 하며 앞면만 출력
    //float stepAngle = XM_2PI / count;
    //VertexColor center(0, 0, 1, 1, 1);
    //float radius = 100.0f;
    //vertices.push_back(center);
    //FOR(count)
    //{
    //    float angle = stepAngle * i;        
    //    vertices.emplace_back(cos(angle) * radius, sin(angle) * radius, 0, 0, 1);
    //}
    //vertices.emplace_back(cos(0) * radius, sin(0) * radius, 0, 0, 1);
    //
    vertices.emplace_back(0, 100, 1, 0, 0);
    vertices.emplace_back(100, -100, 1, 0, 0);
    vertices.emplace_back(-100, -100, 1, 0, 0);

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

    indices = { 0, 1, 2 };

    //FOR(count)
    //{
    //    indices.push_back(0);        
    //    if (i + 2 > count)
    //    {
    //        indices.push_back(1);
    //    }
    //    else
    //    {
    //        indices.push_back(i + 2);
    //    }
    //    indices.push_back(i + 1);
    //
    //}

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    colorBuffer = new ColorBuffer();

    worldBuffer = new MatrixBuffer();
    

    worldMatrix._11 = 1;
    worldMatrix._22 = 1;
    worldMatrix._33 = 1;
    worldMatrix._44 = 1;

    worldMatrix._41 = CENTER_X;
    worldMatrix._42 = CENTER_Y;
}

TutorialScene::~TutorialScene()
{
    delete vertexBuffer;
    delete indexBuffer;
    delete colorBuffer;

    delete worldBuffer;    
}

void TutorialScene::Update()
{
    //if (KEY->Press('W'))
    //    worldMatrix._42 += 100.0f * DELTA;
    //if (KEY->Press('S'))
    //    worldMatrix._42 -= 100.0f * DELTA;
    //if (KEY->Press('A'))
    //    worldMatrix._41 -= 100.0f * DELTA;
    //if (KEY->Press('D'))
    //    worldMatrix._41 += 100.0f * DELTA;

    pos = mousePos;

    if (KEY->Press('W'))
        pos.y += 100.0f * DELTA;
    if (KEY->Press('S'))
        pos.y -= 100.0f * DELTA;
    if (KEY->Press('A'))
        pos.x -= 100.0f * DELTA;
    if (KEY->Press('D'))
        pos.x += 100.0f * DELTA;

    Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

    //if (KEY->Press('T'))
    //    worldMatrix._22 += 1.0f * DELTA;
    //if (KEY->Press('G'))
    //    worldMatrix._22 -= 1.0f * DELTA;
    //if (KEY->Press('F'))
    //    worldMatrix._11 -= 1.0f * DELTA;
    //if (KEY->Press('H'))
    //    worldMatrix._11 += 1.0f * DELTA;

    if (KEY->Press('T'))
        scale.y += 1.0f * DELTA;
    if (KEY->Press('G'))
        scale.y -= 1.0f * DELTA;
    if (KEY->Press('F'))
        scale.x -= 1.0f * DELTA;
    if (KEY->Press('H'))
        scale.x += 1.0f * DELTA;

    Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);

    //static float angle = 0.0f;

    //worldMatrix._11 = cos(angle);
    //worldMatrix._12 = sin(angle);
    //worldMatrix._21 = -sin(angle);
    //worldMatrix._22 = cos(angle);

    if (KEY->Press(VK_UP))
        angle += DELTA;
    if (KEY->Press(VK_DOWN))
        angle -= DELTA;

    Matrix R = XMMatrixRotationZ(angle);

    //float r = Random(0.0f, 1.0f);
    //float g = Random(0.0f, 1.0f);
    //float b = Random(0.0f, 1.0f);
    //
    //colorBuffer->SetColor(r, g, b);

    //worldBuffer->Set(XMLoadFloat4x4(&worldMatrix));
    worldBuffer->Set(S * R * T);
}

void TutorialScene::Render()
{
    worldBuffer->SetVS(0);    

    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    indexBuffer->Set();

    colorBuffer->SetPS(0);

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
    //DC->Draw(vertices.size(), 0);
}

void TutorialScene::PostRender()
{
}
