#include "Application.h"
#include "HeavyTurret.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

HeavyTurret::HeavyTurret(int x, int y) : Enemy(x, y) {

	HeavyTurret_Animation1.PushBack({ 291,2,29,28 });
	HeavyTurret_Animation2.PushBack({ 35,2,29,32 });
	HeavyTurret_Animation3.PushBack({ 419,2,31,28 });
	HeavyTurret_Animation4.PushBack({ 158,2,31,28 });
	HeavyTurret_Animation5.PushBack({ 484,2,29,32 });
	HeavyTurret_Animation6.PushBack({ 96,2,29,32 });
	HeavyTurret_Animation7.PushBack({ 354,2,29,28 });
	HeavyTurret_Animation8.PushBack({ 224,2,29,28 });
	HeavyTurret_Animation9.PushBack({ 64,2,29,32 });
	HeavyTurret_Animation10.PushBack({ 515,2,29,31 });
	HeavyTurret_Animation11.PushBack({ 257,2,29,28 });
	HeavyTurret_Animation12.PushBack({ 322,2,29,28 });
	HeavyTurret_Animation13.PushBack({ 127,2,29,30 });
	HeavyTurret_Animation14.PushBack({ 191,2,29,28 });
	HeavyTurret_Animation15.PushBack({ 452,2,30,30 });
	HeavyTurret_Animation16.PushBack({ 388,2,30,28 });
	HeavyTurret_Death.PushBack({ 1,2,29,28 });


	vida = 4;
	animation = &HeavyTurret_Animation1;
	collider = App->collision->AddCollider({ 0, 0, 29, 28 }, COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION, (Module*)App->enemies);
	current_time = 0;
	dispara = false;
	estat = 0;
}

void HeavyTurret::Move() {
	if (vida > 0) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
			dispara = true;
			current_time = SDL_GetTicks() + 1000;
		}

		rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
		rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
		float angle = atan2(rectaX, rectaY);
		if (angle > 0) {
			if (angle <= 0.375f) {
				animation = &HeavyTurret_Animation2;
				if (dispara == true) {
					iPoint direccio(0, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 0.75f) {
				animation = &HeavyTurret_Animation10;
				if (dispara == true) {
					iPoint direccio(-1, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.25f) {
				animation = &HeavyTurret_Animation5;
				if (dispara == true) {
					iPoint direccio(-2, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.5f) {
				animation = &HeavyTurret_Animation15;
				if (dispara == true) {
					iPoint direccio(-2, -1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.875f) {
				animation = &HeavyTurret_Animation3;
				if (dispara == true) {
					iPoint direccio(-2, 0);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 2.25f) {
				animation = &HeavyTurret_Animation16;
				if (dispara == true) {
					iPoint direccio(-2, 1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 2.625f) {
				animation = &HeavyTurret_Animation7;
				if (dispara == true) {
					iPoint direccio(-2, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 3.0f) {
				animation = &HeavyTurret_Animation12;
				if (dispara == true) {
					iPoint direccio(-1, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
		else {
			if (angle < 0) {
				if (angle >= -0.375f) {
					animation = &HeavyTurret_Animation9;
					if (dispara == true) {
						iPoint direccio(1, -2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -0.75f) {
					animation = &HeavyTurret_Animation6;
					if (dispara == true) {
						iPoint direccio(2, -2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.25f) {
					animation = &HeavyTurret_Animation13;
					if (dispara == true) {
						iPoint direccio(2, -1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.5f) {
					animation = &HeavyTurret_Animation4;
					if (dispara == true) {
						iPoint direccio(2, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.875f) {
					animation = &HeavyTurret_Animation14;
					if (dispara == true) {
						iPoint direccio(2, 1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -2.25f) {
					animation = &HeavyTurret_Animation8;
					if (dispara == true) {
						iPoint direccio(2, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -2.625f) {
					animation = &HeavyTurret_Animation11;
					if (dispara == true) {
						iPoint direccio(1, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -3.0f) {
					animation = &HeavyTurret_Animation1;
					if (dispara == true) {
						iPoint direccio(0, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
		}
	}
	position.y += App->background->speedBackGround;
}

void HeavyTurret::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else {
			if (estat == 0) {
				App->player2->puntuacioP2 += 200;
				type = HEAVY_TURRET_DESTROY;
				estat = 1;
				animation = &HeavyTurret_Death;
			}
		}
		if (vida <= 0 && estat == 1) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
			estat = 2;
			this->collider->type = COLLIDER_NONE;
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
		}
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else {
			if (estat == 0) {
				App->player2->puntuacioP2 += 200;
				type = HEAVY_TURRET_DESTROY;
				estat = 1;
				animation = &HeavyTurret_Death;
			}
		}
		if (vida <= 0 && estat == 1) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
			estat = 2;
			this->collider->type = COLLIDER_NONE;
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
		}
	}
}
void HeavyTurret::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Heavy_Turret, position.x, position.y, &(animation->GetCurrentFrame()));
}