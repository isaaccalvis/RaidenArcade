#include "Application.h"
#include "Enemy_LightShooter.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"



Enemy_LightShooter::Enemy_LightShooter(int x, int y) : Enemy(x, y) {

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);



	//original_y = y;
	LightShooterAnim10.PushBack({ 270, 15, 31, 23 });
	LightShooterAnim1.PushBack({ 11, 15, 22, 30 });
	LightShooterAnim16.PushBack({ 454, 15, 25, 30 });
	LightShooterAnim8.PushBack({ 214, 15, 27, 25 });
	LightShooterAnim2.PushBack({ 35, 17, 32, 28 });
	LightShooterAnim6.PushBack({ 161, 15, 27, 26 });
	LightShooterAnim15.PushBack({ 421, 15, 31, 23 });
	LightShooterAnim14.PushBack({ 389, 15, 31, 23 });
	LightShooterAnim13.PushBack({ 363, 15, 24, 30 });
	LightShooterAnim9.PushBack({ 243, 15, 25, 30 });
	LightShooterAnim11.PushBack({ 303, 15, 31, 23 });
	LightShooterAnim3.PushBack({ 69, 16, 32, 30 });
	LightShooterAnim5.PushBack({ 132, 15, 27, 25 });
	LightShooterAnim4.PushBack({ 103, 15, 27, 26 });
	LightShooterAnim12.PushBack({ 336, 15, 25, 30 });
	LightShooterAnim7.PushBack({ 190, 15, 22, 30 });

	animation = &LightShooterAnim13;
}

void Enemy_LightShooter::Move() {
	if (fase == 0 && position.y < 150)
		if (position.y > 110 && position.y < 130)
			position.y += 2;
		else if (position.y > 130)
			position.y += 1;
		else
			position.y += 3;
	else
		fase = 1;
	if (fase == 1)
		if (position.y > 150 && position.y < 130)
			position.y -= 1;
		else if (position.y > 130)
			position.y -= 2;
		else
			position.y -= 3;

	rectaY = (position.y + 15) - (App->player->PROTA.y + App->player->PROTA.h);
	rectaX = (position.x + 15) - (App->player->PROTA.x + App->player->PROTA.w);
	float angle = atan2(rectaX, rectaY);
	if (angle > 0) {
		if (angle <= 0.375f) {
			animation = &LightShooterAnim1;
		}
		else if (angle <= 0.75f) {
			animation = &LightShooterAnim16;
		}
		else if (angle <= 1.25f) {
			animation = &LightShooterAnim8;
		}
		else if (angle <= 1.5f) {
			animation = &LightShooterAnim15;
		}
		else if (angle <= 1.875f) {
			animation = &LightShooterAnim2;
		}
		else if (angle <= 2.25f) {
			animation = &LightShooterAnim14;
		}
		else if (angle <= 2.625f) {
			animation = &LightShooterAnim6;
		}
		else if (angle <= 3.0f) {
			animation = &LightShooterAnim13;
		}
	}
	else {
		if (angle < 0) {
			if (angle >= -0.375f) {
				animation = &LightShooterAnim9;
			}
			else if (angle >= -0.75f) {
				animation = &LightShooterAnim4;
			}
			else if (angle >= -1.25f) {
				animation = &LightShooterAnim10;
			}
			else if (angle >= -1.5f) {
				animation = &LightShooterAnim3;
			}
			else if (angle >= -1.875f) {
				animation = &LightShooterAnim11;
			}
			else if (angle >= -2.25f) {
				animation = &LightShooterAnim5;
			}
			else if (angle >= -2.625f) {
				animation = &LightShooterAnim12;
			}
			else if (angle >= -3.0f) {
				animation = &LightShooterAnim7;
			}
		}
	}
}

void Enemy_LightShooter::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else
			App->player->puntuacioP1 += 130;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LightExplosion, position.x, position.y, COLLIDER_NONE);
			//App->music->PlayFX(light);
		}
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, position.x + 12, position.y + 12, COLLIDER_NONE);
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else
			App->player2->puntuacioP2 += 130;

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LightExplosion, position.x, position.y, COLLIDER_NONE);
			//App->music->PlayFX(light);
		}
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, position.x + 12, position.y + 12, COLLIDER_NONE);
	}

}


void Enemy_LightShooter::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_LightShooter, position.x/*collider->rect.x*/, position.y, &(animation->GetCurrentFrame()));
}