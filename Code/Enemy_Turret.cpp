#include "Application.h"
#include "Enemy_Turret.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "p2Point.h"

iPoint angleDispar;

Enemy_Turret::Enemy_Turret(int x, int y) : Enemy(x, y) {
	Enemy_Turret_Animation.PushBack({ 20, 73, 30, 28 });
	Enemy_Turret_Animation.speed = 0.2f;
	Enemy_Turret_Animation.loop = false;
	animation = &Enemy_Turret_Animation;

	Enemy_Turret_Animation.PushBack({ 19,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 55,72,33,30 });
	Enemy_Turret_Animation.PushBack({ 91,71,33,31 });
	Enemy_Turret_Animation.PushBack({ 126,71,33,31 });
	Enemy_Turret_Animation.PushBack({ 162,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 200,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 240,71,33,31 });
	Enemy_Turret_Animation.PushBack({ 279,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 315,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 353,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 390,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 428,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 465,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 505,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 544,72,33,31 });
	Enemy_Turret_Animation.PushBack({ 581,72,33,31 });
	vida = 4;
	collider = App->collision->AddCollider({ 0, 0, 30, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Turret::Move() {
	deltaY = (position.y + 15) - (App->player->PROTA.y  + App->player->PROTA.h);
	deltaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
	float angle = atan2(deltaX, deltaY);
	//if (angle > 0) {
	//	if (angle < 0.375f)

	//	else if (angle < 0.75f)

	//	else if (angle < 1.25f)

	//	else if (angle < 1.5f)

	//	else if (angle < 1.875f)

	//	else if (angle < 2.25f)

	//	else if (angle < 2.625f)

	//	else if (angle < 3.0f)

	//}
	//else {
	//	if (angle > 0) {
	//		if (angle > -0.375f)

	//		else if (angle > -0.75f)

	//		else if (angle > -1.25f)

	//		else if (angle > -1.5f)

	//		else if (angle > -1.875f)

	//		else if (angle > -2.25f)

	//		else if (angle > -2.625f)

	//		else if (angle > -3.0f)

	//	}
	//}
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