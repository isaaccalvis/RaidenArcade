#include "Application.h"
#include "HeavyOrangeAirship.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

HeavyOrangeAirship::HeavyOrangeAirship(int x, int y) : Enemy(x, y) {

	vida = 140;
	animation = &HeavyOrangeAirship_Animation;
	HeavyOrangeAirship_Animation.PushBack({ 0,0,127 ,79 });
	HeavyOrangeAirship_Animation.speed = 0.1f;

	HeavyOrangeAirship_AnimationDeixantBomba.PushBack({ 128,0,127 ,79 });
	HeavyOrangeAirship_AnimationDeixantBomba.PushBack({ 256,0,127 ,79 });
	HeavyOrangeAirship_AnimationDeixantBomba.PushBack({ 384,0,127 ,79 });
	HeavyOrangeAirship_AnimationDeixantBomba.speed = 0.1f;
	HeavyOrangeAirship_AnimationDeixantBomba.loop = false;

	collider = App->collision->AddCollider({ 0, 30, 127, 49 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	current_time = SDL_GetTicks() + 10000;
	dispara = false;
}

void HeavyOrangeAirship::Move() {
	position.y -= 0.25f;
	if (current_time - 500 < SDL_GetTicks())
		animation = &HeavyOrangeAirship_AnimationDeixantBomba;
	else
		animation = &HeavyOrangeAirship_Animation;

	if (current_time < SDL_GetTicks()) {
		current_time = SDL_GetTicks() + 5000;
		App->enemies->AddEnemy(BOMB, position.x + 72, position.y + 47);
		App->enemies->AddEnemy(BOMB, position.x + 29, position.y + 47);
		HeavyOrangeAirship_AnimationDeixantBomba.Reset();
	}
}

void HeavyOrangeAirship::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else {
			App->player->puntuacioP1 += 4000;
			App->enemies->AddEnemy(MISSILE_UP, position.x + 40, position.y);
		}
		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x + 30, position.y, COLLIDER_NONE);
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
			App->player2->puntuacioP2 += 4000;
			App->enemies->AddEnemy(MISSILE_UP, position.x + 40, position.y);
		}
		if (vida <= 0) {
			App->particles->AddParticle(App->particles->LargeExplosion, position.x + 30, position.y, COLLIDER_NONE);

			//App->music->PlayFX(tank);
		}
		else {
			App->particles->AddParticle(App->particles->restOfBulletCollision, collider->rect.x, position.y + 12, COLLIDER_NONE);
			//App->music->PlayFX(hit2);
		}
	}
}
void HeavyOrangeAirship::DrawUp() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Heavy_Orange_Airship, position.x, position.y, &(animation->GetCurrentFrame()));
}