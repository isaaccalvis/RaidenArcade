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

HeavyTurret::HeavyTurret(int x, int y) : Enemy(x, y) {

	vida = 1;
	animation = &HeavyTurret_Animation;
	collider = App->collision->AddCollider({ 0, 0, 31, 29 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	current_time = 0;
	dispara = false;
}

void HeavyTurret::Move() {

}

void HeavyTurret::OnCollision(Collider* collider) {
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
void HeavyTurret::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Turret, position.x, position.y, &(animation->GetCurrentFrame()));
}