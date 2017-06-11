#include "Application.h"
#include "vTank.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

vTank::vTank(int x, int y) : Enemy(x, y) {

	vTank_Animation1.PushBack({ 13,16,38,31 });
	vTank_Animation1.PushBack({ 77,16,38,31 });
	vTank_Animation1.PushBack({ 141,16,38,31 });
	vTank_Animation1.PushBack({ 205,16,38,31 });
	vTank_Animation1.speed = 0.1f;
	vTank_Animation1.loop = false;

	vTank_Animation2.PushBack({ 13,58,31,38 });
	vTank_Animation2.PushBack({ 77,58,31,38 });
	vTank_Animation2.PushBack({ 141,56,31,38 });
	vTank_Animation2.PushBack({ 205,56,31,38 });
	vTank_Animation2.speed = 0.1f;
	vTank_Animation2.loop = false;

	vida = 6;

	collider = App->collision->AddCollider({ 0, 0, 31, 29 }, COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION, (Module*)App->enemies);
	current_time = 0;
	dispara = false;

	if (position.x == 240 || position.x == 100) {
		state = 0;
		animation = &vTank_Animation1;
	}
	else {
		state = 1;
		animation = &vTank_Animation2;
	}
	current_time = SDL_GetTicks() + 2500;
	piun = SDL_GetTicks() + 2000;
}

void vTank::Move() {
	if (state == 0) {
		if (current_time >= SDL_GetTicks())
			position.y += App->background->speedBackGround;
		else {
			position.x += 0.5f;
			position.y += App->background->speedBackGround;
			vTank_Animation1.loop = true;
			if (SDL_TICKS_PASSED(SDL_GetTicks(), piun)) {
				if (piun < SDL_GetTicks())
					piun = SDL_GetTicks() + 400;
				else {
					dispara = true;
					piun = SDL_GetTicks() + 400;
				}
			}
		}
	}
	else
	{
		if (current_time >= SDL_GetTicks())
			position.y += App->background->speedBackGround;
		else {
			position.y -= 0.25f;
			vTank_Animation2.loop = true;
			if (SDL_TICKS_PASSED(SDL_GetTicks(), piun)) {
				if (piun < SDL_GetTicks())
					piun = SDL_GetTicks() + 400;
				else {
					dispara = true;
					piun = SDL_GetTicks() + 400;
				}
			}
		}
	}
	if (dispara == true) {
		iPoint direccio(-1, 2);
		App->particles->enemyBulletBasic.speed = direccio;
		App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
		dispara = true;
	}
	if (dispara == true) {
		iPoint direccio(1, 2);
		App->particles->enemyBulletBasic.speed = direccio;
		App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
		dispara = false;
	}
}

void vTank::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else
			App->player->puntuacioP1 += 600;

		if (vida <= 0)
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else
			App->player2->puntuacioP2 += 600;

		if (vida <= 0)
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
	}
}

void vTank::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_vTank, position.x, position.y, &(animation->GetCurrentFrame()));
}