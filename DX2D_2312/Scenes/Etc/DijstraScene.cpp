#include "Framework.h"
#include "DijstraScene.h"

DijstraScene::DijstraScene()
{
    amazon = new Amazon();
    dijkstra = new Dijkstra();
}

DijstraScene::~DijstraScene()
{
    delete dijkstra;
}

void DijstraScene::Update()
{
    if (KEY->Down(VK_LBUTTON))
    {
        int start = dijkstra->FindCloseNode(amazon->GetLocalPosition());
        int end = dijkstra->FindCloseNode(mousePos);

        amazon->SetPath(dijkstra->GetPath(start, end));
    }

    dijkstra->Update();
}

void DijstraScene::Render()
{
    dijkstra->Render();
}

void DijstraScene::PostRender()
{
}
