#include "Application.h"
#include "Enemy_BonusPlane.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

Enemy_BonusPlane::Enemy_BonusPlane(int x, int y) : Enemy(x, y) {
    Enemy_BonusPlane_Animation.PushBack({ 179, 143, 53, 61 });
    Enemy_BonusPlane_Animation.speed = 0.2f;
    Enemy_BonusPlane_Animation.loop = true;
    animation = &Enemy_BonusPlane_Animation;

    vida = 2;
    collider = App->collision->AddCollider({ 0, 0, 53, 61 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
    original_pos.y = y;
    original_pos.x = x;

    path.PushBack({ 0.0f,1.f }, 30, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.0f,0.0f }, 37, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.0f,0.0f }, 3, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.3f,0.2f }, 85, &Enemy_BonusPlane_Animation);
    path.PushBack({ -0.3f,0.2f }, 170, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.3f,0.2f }, 170, &Enemy_BonusPlane_Animation);
    path.PushBack({ -0.3f,0.2f }, 170, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.3f,0.2f }, 85, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.0f,0.0f }, 26, &Enemy_BonusPlane_Animation);
    path.PushBack({ 0.0f,1.f }, 100, &Enemy_BonusPlane_Animation);

}

void Enemy_BonusPlane::Move() {
    position = original_pos + path.GetCurrentPosition();
}

void Enemy_BonusPlane::OnCollision(Collider* collider) {
    if (collider->type == COLLIDER_PLAYER_SHOT)
        vida--;
}
void Enemy_BonusPlane::Draw() {
    if (collider != nullptr)
        collider->SetPos(position.x, position.y);
    if (animation != nullptr)
        App->render->Blit(App->enemies->sprite_BonusPlane, position.x, position.y, &(animation->GetCurrentFrame()));
}