#include "Framework.h"

CookieMelee::CookieMelee(Transform* target)
{
    SetTarget(target);

    LoadClip(PATH, "Cookie_Melee.xml", false);

    clips[0]->SetEvent(bind(&CookieMelee::AttackEnd, this));
    clips[0]->SetEvent(bind(&CookieMelee::ActiveCollider, this), 2);
    clips[0]->SetEvent(bind(&CookieMelee::InactiveCollider, this), 5);

    attackCollider = new RectCollider({ 100, 100 });
    attackCollider->SetParent(target);
    attackCollider->SetTag("AttackCollider");
    attackCollider->Load();
    attackCollider->GetColor()->SetColor(1, 0, 0);
}

void CookieMelee::Update()
{
    Action::Update();

    attackCollider->UpdateWorld();
}

void CookieMelee::Render()
{
    Action::Render();
    attackCollider->Render();
    attackCollider->RenderUI();
}

void CookieMelee::ActiveCollider()
{
    attackCollider->SetActive(true);
    EffectManager::Get()->Play("Slash", attackCollider->GetGlobalPosition());
}

void CookieMelee::InactiveCollider()
{
    attackCollider->SetActive(false);
}

void CookieMelee::AttackEnd()
{
    Observer::Get()->ExcuteIntEvent("SetAction", Cookie::State::JUMP_DOWN);
}
