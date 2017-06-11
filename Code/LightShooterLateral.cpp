#include "Application.h"
#include "LightShooterLateral.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"


LightShooterLateral::LightShooterLateral(int x, int y) : Enemy(x, y) {

	LightShooterLateral_Animation1.PushBack({ 3,2,26,25 });
	LightShooterLateral_Animation2.PushBack({ 34,2,27,27 });
	LightShooterLateral_Animation3.PushBack({ 65,2,30,27 });
	LightShooterLateral_Animation4.PushBack({ 97,2,29,26 });
	LightShooterLateral_Animation5.PushBack({ 131,2,26,25 });
	LightShooterLateral_Animation6.PushBack({ 162,2,27,26 });
	LightShooterLateral_Animation7.PushBack({ 193,2,29,27 });
	LightShooterLateral_Animation8.PushBack({ 226,2,28,26 });
	LightShooterLateral_Animation9.PushBack({ 259,2,26,25 });
	LightShooterLateral_Animation10.PushBack({ 290,2,27,27 });
	LightShooterLateral_Animation11.PushBack({ 321,2,29,27 });
	LightShooterLateral_Animation12.PushBack({ 353,2,29,26 });
	LightShooterLateral_Animation13.PushBack({ 387,2,25,25 });
	LightShooterLateral_Animation14.PushBack({ 418,2,28,26 });
	LightShooterLateral_Animation15.PushBack({ 449,2,29,27 });
	LightShooterLateral_Animation16.PushBack({ 482,2,28,26 });

	vida = 1;
	animation = &LightShooterLateral_Animation9;
	collider = App->collision->AddCollider({ 0, 0, 30, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	current_time = SDL_GetTicks() + 800;
	dispara = false;

	if (position.x < 150)
		state = 0;
	else
		state = 1;
}

void LightShooterLateral::Move() {
	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
		dispara = true;
		current_time = SDL_GetTicks() + 2000;
	}
	if (state == 0) {
		if (fase == 0 && position.y < 150)
			if (position.y > 110 && position.y < 130) {
				position.y += 2;
				position.x += 2;
			}
			else if (position.y > 130) {
				position.y += 1;
				position.x += 1;
			}
			else {
				position.y += 3;
				position.x += 3;
			}
		else
			fase = 1;
		if (fase == 1)
			if (position.y > 150 && position.y < 130) {
				position.y -= 1;
				position.x += 1;
			}
			else if (position.y > 130) {
				position.y -= 2;
				position.x += 2;
			}
			else {
				position.y -= 3;
				position.x += 3;
			}

			rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
			rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
			float angle = atan2(rectaX, rectaY);
			if (angle > 0) {
				if (angle <= 0.375f) {
					animation = &LightShooterLateral_Animation1;
				}
				else if (angle <= 0.75f) {
					animation = &LightShooterLateral_Animation16;
				}
				else if (angle <= 1.25f) {
					animation = &LightShooterLateral_Animation15;
				}
				else if (angle <= 1.5f) {
					animation = &LightShooterLateral_Animation14;
				}
				else if (angle <= 1.875f) {
					animation = &LightShooterLateral_Animation13;
				}
				else if (angle <= 2.25f) {
					animation = &LightShooterLateral_Animation12;
				}
				else if (angle <= 2.625f) {
					animation = &LightShooterLateral_Animation11;
				}
				else if (angle <= 3.0f) {
					animation = &LightShooterLateral_Animation10;
				}
			}
			else {
				if (angle < 0) {
					if (angle >= -0.375f) {
						animation = &LightShooterLateral_Animation2;
					}
					else if (angle >= -0.75f) {
						animation = &LightShooterLateral_Animation3;
					}
					else if (angle >= -1.25f) {
						animation = &LightShooterLateral_Animation4;
					}
					else if (angle >= -1.5f) {
						animation = &LightShooterLateral_Animation5;
					}
					else if (angle >= -1.875f) {
						animation = &LightShooterLateral_Animation6;
					}
					else if (angle >= -2.25f) {
						animation = &LightShooterLateral_Animation7;
					}
					else if (angle >= -2.625f) {
						animation = &LightShooterLateral_Animation8;
					}
					else if (angle >= -3.0f) {
						animation = &LightShooterLateral_Animation9;
					}
				}
			}
	}
	else {
		if (fase == 0 && position.y < 150)
			if (position.y > 110 && position.y < 130) {
				position.y += 2;
				position.x -= 2;
			}
			else if (position.y > 130) {
				position.y += 1;
				position.x -= 1;
			}
			else {
				position.y += 3;
				position.x -= 3;
			}
		else
			fase = 1;
		if (fase == 1)
			if (position.y > 150 && position.y < 130) {
				position.y -= 1;
				position.x -= 1;
			}
			else if (position.y > 130) {
				position.y -= 2;
				position.x -= 2;
			}
			else {
				position.y -= 3;
				position.x -= 3;
			}
	}
	rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
	rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
	float angle = atan2(rectaX, rectaY);
	if (angle > 0) {
		if (angle <= 0.375f) {
			animation = &LightShooterLateral_Animation1;
			if (dispara == true) {
				iPoint direccio(0, -2);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 0.75f) {
			animation = &LightShooterLateral_Animation16;
			if (dispara == true) {
				iPoint direccio(-1, -2);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 1.25f) {
			animation = &LightShooterLateral_Animation15;
			if (dispara == true) {
				iPoint direccio(-2, -2);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 1.5f) {
			animation = &LightShooterLateral_Animation14;
			if (dispara == true) {
				iPoint direccio(-2, -1);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 1.875f) {
			animation = &LightShooterLateral_Animation13;
			if (dispara == true) {
				iPoint direccio(-2, 0);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 2.25f) {
			animation = &LightShooterLateral_Animation12;
			if (dispara == true) {
				iPoint direccio(-2, 1);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 2.625f) {
			animation = &LightShooterLateral_Animation11;
			if (dispara == true) {
				iPoint direccio(-2, 2);
				App->particles->enemyBulletBasic.speed = direccio;
				App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
				dispara = false;
			}
		}
		else if (angle <= 3.0f) {
			animation = &LightShooterLateral_Animation10;
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
				animation = &LightShooterLateral_Animation2;
				if (dispara == true) {
					iPoint direccio(1, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -0.75f) {
				animation = &LightShooterLateral_Animation3;
				if (dispara == true) {
					iPoint direccio(2, -2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -1.25f) {
				animation = &LightShooterLateral_Animation4;
				if (dispara == true) {
					iPoint direccio(2, -1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -1.5f) {
				animation = &LightShooterLateral_Animation5;
				if (dispara == true) {
					iPoint direccio(2, 0);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -1.875f) {
				animation = &LightShooterLateral_Animation6;
				if (dispara == true) {
					iPoint direccio(2, 1);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -2.25f) {
				animation = &LightShooterLateral_Animation7;
				if (dispara == true) {
					iPoint direccio(2, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -2.625f) {
				animation = &LightShooterLateral_Animation8;
				if (dispara == true) {
					iPoint direccio(1, 2);
					App->particles->enemyBulletBasic.speed = direccio;
					App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
					dispara = false;
				}
			}
			else if (angle >= -3.0f) {
				animation = &LightShooterLateral_Animation9;
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


void LightShooterLateral::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else
			App->player->puntuacioP1 += 200;

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
			App->player2->puntuacioP2 += 200;

		if (vida <= 0)
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
	}
}

void LightShooterLateral::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Light_Shooter_Lateral, position.x, position.y, &(animation->GetCurrentFrame()));
}