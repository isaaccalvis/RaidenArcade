#include "Application.h"
#include "Enemy_Turret.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"

#include "SDL\include\SDL_timer.h"

iPoint angleDispar;



Enemy_Turret::Enemy_Turret(int x, int y) : Enemy(x, y) {



		Enemy_Turret_Animation1.PushBack({ 20,73,31,29 });
		Enemy_Turret_Animation2.PushBack({ 56,72,31,29 });
		Enemy_Turret_Animation3.PushBack({ 92,72,31,29 });
		Enemy_Turret_Animation4.PushBack({ 127,72,31,29 });
		Enemy_Turret_Animation5.PushBack({ 163,73,31,29 });
		Enemy_Turret_Animation6.PushBack({ 201,73,31,29 });
		Enemy_Turret_Animation7.PushBack({ 241,72,31,29 });
		Enemy_Turret_Animation8.PushBack({ 280,73,31,29 });
		Enemy_Turret_Animation9.PushBack({ 316,73,31,29 });
		Enemy_Turret_Animation10.PushBack({ 354,73,31,29 });
		Enemy_Turret_Animation11.PushBack({ 391,73,31,29 });
		Enemy_Turret_Animation12.PushBack({ 429,73,31,29 });
		Enemy_Turret_Animation13.PushBack({ 466,73,31,29 });
		Enemy_Turret_Animation14.PushBack({ 506,73,31,29 });
		Enemy_Turret_Animation15.PushBack({ 545,73,31,29 });
		Enemy_Turret_Animation16.PushBack({ 582,73,31,29 });
		vida = 4;
		animation = &Enemy_Turret_Animation1;
		collider = App->collision->AddCollider({ 0, 0, 31, 29 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
		current_time = 0;
		dispara = false;
	}

	void Enemy_Turret::Move() {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
			if (current_time < SDL_GetTicks())
				current_time = SDL_GetTicks() + 1000;
			else {
				dispara = true;
				current_time = SDL_GetTicks() + 1000;
			}
		}

		rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
		rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
		float angle = atan2(rectaX, rectaY);

		if (angle > 0) {
			if (angle <= 0.375f) {
				animation = &Enemy_Turret_Animation2;
				if (dispara == true) {
					iPoint direccio(0, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 0.75f) {
				animation = &Enemy_Turret_Animation10;
				if (dispara == true) {
					iPoint direccio(-1, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.25f) {
				animation = &Enemy_Turret_Animation5;
				if (dispara == true) {
					iPoint direccio(-2, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.5f) {
				animation = &Enemy_Turret_Animation15;
				if (dispara == true) {
					iPoint direccio(-2, -1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.875f) {
				animation = &Enemy_Turret_Animation3;
				if (dispara == true) {
					iPoint direccio(-2, 0);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 2.25f) {
				animation = &Enemy_Turret_Animation16;
				if (dispara == true) {
					iPoint direccio(-2, 1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 2.625f) {
				animation = &Enemy_Turret_Animation7;
				if (dispara == true) {
					iPoint direccio(-2, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 3.0f) {
				animation = &Enemy_Turret_Animation12;
				if (dispara == true) {
					iPoint direccio(-1, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
		else {
			if (angle < 0) {
				if (angle >= -0.375f) {
					animation = &Enemy_Turret_Animation9;
					if (dispara == true) {
						iPoint direccio(1, -2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -0.75f) {
					animation = &Enemy_Turret_Animation6;
					if (dispara == true) {
						iPoint direccio(2, -2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.25f) {
					animation = &Enemy_Turret_Animation13;
					if (dispara == true) {
						iPoint direccio(2, -1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.5f) {
					animation = &Enemy_Turret_Animation4;
					if (dispara == true) {
						iPoint direccio(2, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.875f) {
					animation = &Enemy_Turret_Animation14;
					if (dispara == true) {
						iPoint direccio(2, 1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -2.25f) {
					animation = &Enemy_Turret_Animation8;
					if (dispara == true) {
						iPoint direccio(2, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -2.625f) {
					animation = &Enemy_Turret_Animation11;
					if (dispara == true) {
						iPoint direccio(1, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -3.0f) {
					animation = &Enemy_Turret_Animation1;
					if (dispara == true) {
						iPoint direccio(0, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
		}
		position.y += App->background->speedBackGround;
	}

void Enemy_Turret::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else
			App->player->puntuacioP1 += 180;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
			//App->music->PlayFX(tank);
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
			App->player2->puntuacioP2 += 180;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
			//App->music->PlayFX(tank);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
			//App->music->PlayFX(hit2);
		}
	}

}
void Enemy_Turret::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Turret, position.x, position.y, &(animation->GetCurrentFrame()));
}