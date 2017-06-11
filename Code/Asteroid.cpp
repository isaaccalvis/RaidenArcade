#include "Application.h"
#include "Asteroid.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Asteroid::Asteroid(int x, int y) : Enemy(x, y) {

	vida = 3;
	Asteroid_Animation.PushBack({ 0,0,31,24 });
	animation = &Asteroid_Animation;
	collider = App->collision->AddCollider({ 0, 0, 31, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	if (x <= 150)
		direccio = 1;
	if (x > 150)
		direccio = 2;
}

void Asteroid::Move() {
	if (direccio == 1) {
		position.y += 2;
		position.x += 0.7f;
	}
	if (direccio == 2){
		position.y += 2;
		position.x -= 0.7f;
	}
}

void Asteroid::OnCollision(Collider* collider) {
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

void Asteroid::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Asteroid, position.x, position.y, &(animation->GetCurrentFrame()));
}