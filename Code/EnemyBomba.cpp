#include "Application.h"
#include "EnemyBomba.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"
#include "ModuleEnemies.h"

Enemy_Bomb::Enemy_Bomb(int x, int y) : Enemy(x, y) {
	Enemy_Enemy_Bomb_Animation.PushBack({ 0,0,24,33 });
	Enemy_Enemy_Bomb_Animation.PushBack({ 25,0,24,33 });
	Enemy_Enemy_Bomb_Animation.PushBack({ 49,0,24,33 });
	Enemy_Enemy_Bomb_Animation.speed = 0.2f;
	Enemy_Enemy_Bomb_Animation.loop = true;
	animation = &Enemy_Enemy_Bomb_Animation;

	vida = 17;
	collider = App->collision->AddCollider({ 0, 0, 24, 33 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_Bomb::Move() {
	position.y += 0.6f;
}

void Enemy_Bomb::OnCollision(Collider* collider) {
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
			iPoint direccio0(0, 3);
			iPoint direccio1(2, 2);
			iPoint direccio2(3, 0);
			iPoint direccio3(2, -2);
			iPoint direccio_1(-2, -2);
			iPoint direccio_2(-3, 0);
			iPoint direccio_3(-2, 2);
			iPoint direccio4(0, -3);

			App->particles->enemyBulletBasic.speed = direccio0;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio1;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio2;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio_1;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio_2;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio_3;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio3;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio4;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);

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
			App->player2->puntuacioP2 += 480;
			App->enemies->AddEnemy(POWER_UP, position.x + 26, position.y + 30);
		}

		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x, position.y, COLLIDER_NONE);
			iPoint direccio0(0, 2);
			iPoint direccio1(2, 2);
			iPoint direccio2(2, 0);
			iPoint direccio3(2, -2);
			iPoint direccio_1(-2, -2);
			iPoint direccio_2(-2, 0);
			iPoint direccio_3(-2, 2);
			iPoint direccio4(0, -2);

			App->particles->enemyBulletBasic.speed = direccio0;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio1;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio2;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio_1;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio_2;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio_3;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio3;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);
			App->particles->enemyBulletBasic.speed = direccio4;
			App->particles->AddParticle(App->particles->enemyBulletBasic, position.x + 15 - 3/* 3 es l'amplada /2 de la bala */, position.y + 15, COLLIDER_ENEMY_SHOT);

		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
		}
	}
}
void Enemy_Bomb::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_enemyBomb, position.x, position.y, &(animation->GetCurrentFrame()));
}