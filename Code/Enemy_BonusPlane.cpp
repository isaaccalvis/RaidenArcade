#include "Application.h"
#include "Enemy_BonusPlane.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"




Enemy_BonusPlane::Enemy_BonusPlane(int x, int y) : Enemy(x, y) {
	Enemy_BonusPlane_Animation.PushBack({ 17, 10, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 82, 10, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 17, 78, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 82, 78, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 17, 144, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 82, 144, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 17, 216, 55, 61 });
	Enemy_BonusPlane_Animation.PushBack({ 82, 216, 55, 61 });
	Enemy_BonusPlane_Animation.speed = 0.2f;
	Enemy_BonusPlane_Animation.loop = true;
	animation = &Enemy_BonusPlane_Animation;

	vida = 17;
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
	dispara = false;
}

void Enemy_BonusPlane::Move() {
	position = original_pos + path.fGetCurrentPosition();

	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
		if (current_time < SDL_GetTicks())
			current_time = SDL_GetTicks() + 2000;
		else {
			dispara = true;
			current_time = SDL_GetTicks() + 2000;
		}
	}

	if (dispara == true) {
		iPoint direccio(0, 2);
		App->particles->enemyBulletBasic.speed = direccio;
		App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
		dispara = true;
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

void Enemy_BonusPlane::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else {
			App->player->puntuacioP1 += 480;
			App->enemies->AddEnemy(POWER_UP, position.x + 26, position.y + 30);
		}

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x, position.y, COLLIDER_NONE);
			//App->music->PlayFX(Bonus);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
			//App->music->PlayFX(hit);
		}
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else {
			App->player2->puntuacioP2 += 480;
			App->enemies->AddEnemy(POWER_UP, position.x + 26, position.y + 30);
		}

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x, position.y, COLLIDER_NONE);
			//App->music->PlayFX(Bonus);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
			//App->music->PlayFX(hit);
		}
	}
}
void Enemy_BonusPlane::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_BonusPlane, position.x, position.y, &(animation->GetCurrentFrame()));
}