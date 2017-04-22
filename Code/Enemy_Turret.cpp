#include "Application.h"
#include "Enemy_Turret.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

Enemy_Turret::Enemy_Turret(int x, int y) : Enemy(x, y) {
	Enemy_Turret_Animation.PushBack({ 20, 73, 30, 28 });
	Enemy_Turret_Animation.speed = 0.2f;
	Enemy_Turret_Animation.loop = false;
	animation = &Enemy_Turret_Animation;

	vida = 4;
	collider = App->collision->AddCollider({ 0, 0, 30, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Turret::Move() {
	position.y += App->background->speedBackGround;
}

void Enemy_Turret::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT)
		vida--;
}
void Enemy_Turret::Draw() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Turret, position.x, position.y, &(animation->GetCurrentFrame()));
}