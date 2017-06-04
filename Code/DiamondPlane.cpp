#include "Application.h"
#include "DiamondPlane.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

DiamondPlane::DiamondPlane(int x, int y) : Enemy(x, y) {

	vida = 40;
	animation = &DiamondPlane_Animation;
	DiamondPlane_Animation.PushBack({ 0,0,79,36 });
	DiamondPlane_Animation.PushBack({ 81,0,79,36 });
	DiamondPlane_Animation.PushBack({ 0,38,79,36 });
	DiamondPlane_Animation.PushBack({ 81,38,79,36 });
	DiamondPlane_Animation.PushBack({ 0,76,79,36});
	DiamondPlane_Animation.speed = 0.05f;
	DiamondPlane_Animation.loop = true;

	collider = App->collision->AddCollider({ 0, 0, 79, 36 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	current_time = 0;
	dispara = false;
	if (position.x < 50)
		move = 1;
	else if (position.x > 200)
		move = 2;
	else
		move = 3;
}

void DiamondPlane::Move() {
	switch (move) {
	case 1:
		position.x += 0.3f;
		position.y += 0.2f;
		break;
	case 2:
		position.x -= 0.3f;
		position.y += 0.2f;
		break;
	case 3:
		position.y += 0.4f;
		break;
	}

	// SHOOT
	if (current_time < SDL_GetTicks()) {
		current_time = SDL_GetTicks() + 1000;
		iPoint a1(0, 3);
		App->particles->enemyBulletBasic.speed = a1;
		App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15, position.y + 33, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 64, position.y + 33, COLLIDER_ENEMY_SHOT);
	}
}

void DiamondPlane::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else {
			App->player->puntuacioP1 += 480;
			App->enemies->AddEnemy(POWER_UP, position.x, position.y);
		}
		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x + 10, position.y, COLLIDER_NONE);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
			//App->music->PlayFX(hit2);
		}
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else
			App->player2->puntuacioP2 += 480;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x + 10, position.y, COLLIDER_NONE);
			//App->music->PlayFX(tank);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
			//App->music->PlayFX(hit2);
		}
	}
}
void DiamondPlane::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Diamond_Plane, position.x, position.y, &(animation->GetCurrentFrame()));
}