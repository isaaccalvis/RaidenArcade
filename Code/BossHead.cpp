#include "Application.h"
#include "BossHead.h"
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

bossHead::bossHead(int x, int y) : Enemy(x, y) {
	bossHead_Animation1.PushBack({ 0, 0, 32, 32 });
	bossHead_Animation2.PushBack({ 0, 32, 32, 32 });
	bossHead_Animation3.PushBack({ 0, 64, 32, 32 });
	bossHead_Animation4.PushBack({ 0, 96, 32, 32 });
	bossHead_Animation5.PushBack({ 0, 128, 32, 32 });
	bossHead_Animation6.PushBack({ 0, 160, 32, 32 });
	bossHead_Animation7.PushBack({ 0, 192, 32, 32 });
	bossHead_Animation8.PushBack({ 0, 224, 32, 32 });
	bossHead_Animation9.PushBack({ 0, 256, 32, 32 });

	vida = 100;
	animation = &bossHead_Animation1;
	collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	current_time = SDL_GetTicks() + 50;
	dispara = false;
}

bossHead::~bossHead() {}

void bossHead::Move() {

	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
		dispara = true;
		current_time = SDL_GetTicks() + 1000;
	}

	rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
	rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
	float angle = atan2(rectaX, rectaY);

	if (angle > 0) {
		if (angle <= 1.5f) {
			animation = &bossHead_Animation9;
			if (dispara == true) {
				if (vida < 50) {
					iPoint direccio(-2, 0);
					iPoint direccio2(-2, -1);
					iPoint direccio3(-2, +1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio2;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio3;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
				else {
					iPoint direccio(-2, -0);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
		else if (angle <= 1.875f) {
			animation = &bossHead_Animation7;
			if (dispara == true) {
				if (vida < 50) {
					iPoint direccio(-2, 0);
					iPoint direccio2(-2, -1);
					iPoint direccio3(-2, 1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio2;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio3;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
				else {
					iPoint direccio(-2, 0);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
		else if (angle <= 2.25f) {
			animation = &bossHead_Animation6;
			if (dispara == true) {
				if (vida < 50) {
					iPoint direccio(-3, 0);
					iPoint direccio2(-3, 1);
					iPoint direccio3(-2, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio2;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio3;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
				else {
					iPoint direccio(-2, 1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
		else if (angle <= 2.625f) {
			animation = &bossHead_Animation5;
			if (dispara == true) {
				if (vida < 50) {
					iPoint direccio(-3, 1);
					iPoint direccio2(-3, 2);
					iPoint direccio3(-2, 3);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio2;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio3;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
				else {
					iPoint direccio(-2, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
		else{
			animation = &bossHead_Animation1;
			if (dispara == true) {
				if (vida < 50) {
					iPoint direccio(-2, 1);
					iPoint direccio2(-2, 2);
					iPoint direccio3(-1, 3);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio2;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					App->particles->enemyBulletBasic.speed = direccio3;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
				else {
					iPoint direccio(-1, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
		}
	}
	else {
		if (angle < 0) {
			if (angle >= -1.5f) {
				animation = &bossHead_Animation4;
				if (dispara == true) {
					if (vida < 50) {
						iPoint direccio(-2, 0);
						iPoint direccio2(-2, -1);
						iPoint direccio3(-2, +1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio2;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio3;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
					else {
						iPoint direccio(2, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
			else if (angle >= -1.875f) {
				animation = &bossHead_Animation2;
				if (dispara == true) {
					if (vida < 50) {
						iPoint direccio(2, -1);
						iPoint direccio2(3, 1);
						iPoint direccio3(3, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio2;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio3;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
					else {
						iPoint direccio(2, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
			else if (angle >= -2.25f) {
				animation = &bossHead_Animation3;
				if (dispara == true) {
					if (vida < 50) {

						iPoint direccio(2, 2);
						iPoint direccio2(3, 1);
						iPoint direccio3(3, 0);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio2;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio3;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;

					}
					else {
						iPoint direccio(2, 1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
			else if (angle >= -2.625f) {
				animation = &bossHead_Animation8;
				if (dispara == true) {
					if (vida < 50) {
						iPoint direccio(2, 3);
						iPoint direccio2(3, 2);
						iPoint direccio3(3, 1);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio2;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio3;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
					else {
						iPoint direccio(2, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
			else {
				animation = &bossHead_Animation1;
				if (dispara == true) {
					if (vida < 50) {
						iPoint direccio(0, 2);
						iPoint direccio2(-1, 2);
						iPoint direccio3(1, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio2;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						App->particles->enemyBulletBasic.speed = direccio3;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
					else {
						iPoint direccio(0, 2);
						App->particles->enemyBulletBasic.speed = direccio;
						App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
						dispara = false;
					}
				}
			}
		}
	}
	//position.y += App->background->speedBackGround;
}

void bossHead::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else
			App->player->puntuacioP1 += 2500;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
		}
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else
			App->player2->puntuacioP2 += 2500;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
		}
	}

}
void bossHead::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_boss6, position.x, position.y, &(animation->GetCurrentFrame()));
}