#include "Application.h"
#include "Enemy.h"
#include "Enemy_BasicTank.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

Enemy_BasicTank::Enemy_BasicTank(int x, int y) : Enemy(x, y) {
	Enemy_BasicTank_Animation1.PushBack({ 74, 60, 36, 34 });
	Enemy_BasicTank_Animation2.PushBack({ 38, 60, 36, 34 });
	Enemy_BasicTank_Animation3.PushBack({ 110, 60, 36, 34 });
	Enemy_BasicTank_Animation4.PushBack({ 221, 60, 36, 34 });
	Enemy_BasicTank_Animation5.PushBack({ 256, 60, 36, 34 });
	Enemy_BasicTank_Animation6.PushBack({ 148, 60, 36, 34 });
	Enemy_BasicTank_Animation7.PushBack({ 2, 60, 36, 34 });
	Enemy_BasicTank_Animation8.PushBack({ 186, 60, 36, 34 });
	Enemy_BasicTank_Animation9.PushBack({ 436, 60, 36, 34 });
	Enemy_BasicTank_Animation10.PushBack({ 472, 60, 36, 34 });
	Enemy_BasicTank_Animation11.PushBack({ 507, 60, 36, 34 });
	Enemy_BasicTank_Animation12.PushBack({ 543, 60, 36, 34 });
	Enemy_BasicTank_Animation13.PushBack({ 291, 60, 36, 34 });
	Enemy_BasicTank_Animation14.PushBack({ 326, 60, 36, 34 });
	Enemy_BasicTank_Animation15.PushBack({ 364, 60, 36, 34 });
	Enemy_BasicTank_Animation16.PushBack({ 400, 60, 36, 34 });
	Enemy_BasicTank_Death.PushBack({ 36,16,36,34 });

	animation = &Enemy_BasicTank_Animation7;

	current_time = SDL_GetTicks() + 2000;

	vida = 2;
	collider = App->collision->AddCollider({ 5, 10, 34, 25 }, COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION, (Module*)App->enemies);
	piun = 0;
	dispara = false;
	estat = 0;
}

void Enemy_BasicTank::Move() {
	int flyingTank = 0;
	if (position.x == 20)
		flyingTank = 1;

	if (vida > 0) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), piun)) {
			dispara = true;
			piun = SDL_GetTicks() + 2000;
		}
		if (flyingTank = 0) {
			if (current_time >= SDL_GetTicks()) {
				position.y += App->background->speedBackGround;
			}
			else {
				position.x += 0.5f;
				position.y += App->background->speedBackGround;
			}
		}
		else {
			if (current_time >= SDL_GetTicks()) {
				position.y += App->background->speedBackGround;
			}
			else if (SDL_GetTicks() < current_time + 2000) {
				position.x += 0.5f;
				position.y += App->background->speedBackGround;
			}
			else
				position.y += App->background->speedBackGround;
		}

		rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
		rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
		float angle = atan2(rectaX, rectaY);
		if (angle > 0) {
			if (angle <= 0.375f) {
				animation = &Enemy_BasicTank_Animation1;
				if (dispara == true) {
					iPoint direccio(0, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 0.75f) {
				animation = &Enemy_BasicTank_Animation16;
				if (dispara == true) {
					iPoint direccio(-1, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.25f) {
				animation = &Enemy_BasicTank_Animation8;
				if (dispara == true) {
					iPoint direccio(-2, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.5f) {
				if (dispara == true) {
					animation = &Enemy_BasicTank_Animation15;
					iPoint direccio(-2, -1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 1.875f) {
				animation = &Enemy_BasicTank_Animation2;
				if (dispara == true) {
					iPoint direccio(-2, 0);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 2.25f) {
				animation = &Enemy_BasicTank_Animation14;
				if (dispara == true) {
					iPoint direccio(-2, 1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 2.625f) {
				animation = &Enemy_BasicTank_Animation6;
				if (dispara == true) {
					iPoint direccio(-2, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle <= 3.0f) {
				animation = &Enemy_BasicTank_Animation13;
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
					animation = &Enemy_BasicTank_Animation9;
					if (dispara == true) {
						iPoint direccio(1, -2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -0.75f) {
					animation = &Enemy_BasicTank_Animation4;
					if (dispara == true) {
						iPoint direccio(2, -2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.25f) {
					animation = &Enemy_BasicTank_Animation10;
					if (dispara == true) {
						iPoint direccio(2, -1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.5f) {
					animation = &Enemy_BasicTank_Animation3;
					if (dispara == true) {
						iPoint direccio(2, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -1.875f) {
					animation = &Enemy_BasicTank_Animation11;
					if (dispara == true) {
						iPoint direccio(2, 1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -2.25f) {
					animation = &Enemy_BasicTank_Animation5;
					if (dispara == true) {
						iPoint direccio(2, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -2.625f) {
					animation = &Enemy_BasicTank_Animation12;
					if (dispara == true) {
						iPoint direccio(1, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
				else if (angle >= -3.0f) {
					animation = &Enemy_BasicTank_Animation7;
					if (dispara == true) {
						iPoint direccio(0, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
		}
	}
	else
		position.y += 0.3f;
}

void Enemy_BasicTank::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else {
			if (estat == 0) {
				App->player->puntuacioP1 += 130;
				type = BASIC_TANK_DESTROY;
				estat = 1;
				animation = &Enemy_BasicTank_Death;
			}
		}

		if (vida <= 0 && estat == 1) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
			estat = 2;
			this->collider->type = COLLIDER_NONE;
		}
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, position.x + 12, position.y + 12, COLLIDER_NONE);
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else {
			if (estat == 0) {
				App->player2->puntuacioP2 += 130;
				type = BASIC_TANK_DESTROY;
				estat = 1;
				animation = &Enemy_BasicTank_Death;
			}
		}
		if (vida <= 0 && estat == 1) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
			estat = 2;
			this->collider->type = COLLIDER_NONE;
		}
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, position.x + 12, position.y + 12, COLLIDER_NONE);
	}

}
void Enemy_BasicTank::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_BasicTank, position.x /*collider->rect.x*/, position.y, &(animation->GetCurrentFrame()));
}