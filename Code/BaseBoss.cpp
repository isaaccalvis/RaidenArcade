#include "Application.h"
#include "BaseBoss.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"
Base_Boss::Base_Boss(int x, int y) : Enemy(x, y) {

	vida = 1;
	Base_Boss_Animation.PushBack({ 122, 133, 86, 50 });

	Base_Boss_DestruccioAnimation.PushBack({ 112, 0, 86, 35 });

	Base_Boss_Dreta.PushBack({ 122, 133, 86, 50 });
	Base_Boss_Dreta.PushBack({ 208, 133, 86, 50 });
	Base_Boss_Dreta.PushBack({ 294, 133, 86, 50 });
	Base_Boss_Dreta.PushBack({ 380, 133, 86, 50 });
	Base_Boss_Dreta.PushBack({ 466, 133, 86, 50 });
	Base_Boss_Dreta.PushBack({ 552, 133, 86, 50 });
	Base_Boss_Dreta.PushBack({ 638, 133, 86, 50 });
	Base_Boss_Dreta.loop = true;
	Base_Boss_Dreta.speed = 0.2f;

	Base_Boss_Esquerra.PushBack({ 122, 228, 86, 50 });
	Base_Boss_Esquerra.PushBack({ 208, 228, 86, 50 });
	Base_Boss_Esquerra.PushBack({ 294, 228, 86, 50 });
	Base_Boss_Esquerra.PushBack({ 380, 228, 86, 50 });
	Base_Boss_Esquerra.PushBack({ 466, 228, 86, 50 });
	Base_Boss_Esquerra.PushBack({ 552, 228, 86, 50 });
	Base_Boss_Esquerra.PushBack({ 638, 228, 86, 50 });
	Base_Boss_Esquerra.loop = true;
	Base_Boss_Esquerra.speed = 0.2f;

	Base_Boss_Inicia.PushBack({ 201, 0, 79, 48 });
	Base_Boss_Inicia.PushBack({ 280, 0, 79, 48 });
	Base_Boss_Inicia.PushBack({ 359, 0, 79, 48 });
	Base_Boss_Inicia.PushBack({ 438, 0, 79, 48 });
	Base_Boss_Inicia.PushBack({ 517, 0, 79, 48 });
	Base_Boss_Inicia.PushBack({ 596, 0, 79, 48 });
	Base_Boss_Inicia.PushBack({ 675, 0, 79, 48 });
	Base_Boss_Inicia.loop = true;
	Base_Boss_Inicia.speed = 0.2f;

	animation = &Base_Boss_Inicia;
	current_time = 0;
	estat = 0;
}

void Base_Boss::Move() {
	if (estat == 0) {
		estat = -4;	// ANIMACIO INICIAL
		current_time = SDL_GetTicks() + 3000;
	}
	else if (estat != -4) {
		if (capsBoss[0] != -1)
			capsBoss[0] = App->enemies->moveCap(capsBoss[0], position.x + 4, position.y + 2);
		if (capsBoss[1] != -1)
			capsBoss[1] = App->enemies->moveCap(capsBoss[1], position.x + 45, position.y + 2);

		if (estat == 1) {	// CANVI DE DIRECCIO
			position.x += 0.2f;
			if (SDL_GetTicks() > current_time) {
				estat = -3;
				animation = &Base_Boss_Animation;
				current_time = SDL_GetTicks() + 2000;
			}
		}
		else if (estat == -1) {
			position.x -= 0.2f;
			if (SDL_GetTicks() > current_time) {
				estat = -2;
				animation = &Base_Boss_Animation;
				current_time = SDL_GetTicks() + 2000;
			}
		}
		else if (estat == -2) { // pausa al arrivar a una banda
			if (SDL_GetTicks() > current_time) {
				estat = 1;
				animation = &Base_Boss_Dreta;
				current_time = SDL_GetTicks() + 5000;
			}
		}
		else if (estat == -3) { // pausa al arrivar a una banda
			if (SDL_GetTicks() > current_time) {
				estat = -1;
				animation = &Base_Boss_Esquerra;
				current_time = SDL_GetTicks() + 5000;
			}
		}

		if (capsBoss[0] == -1 && capsBoss[1] == -1 && estat < 2) {	// QUAN ES MOR
			animation = &Base_Boss_DestruccioAnimation;
			estat = 2;
			App->background->contadorAuxiliarBoss++;
			current_time = SDL_GetTicks() + 500;
		}
		if (estat >= 2 && estat < 10) {	// EXPLOSIO QUAN MOE
			if (current_time < SDL_GetTicks()) {
				switch (estat) {
				case 1:
				case 4:
				case 6:
					App->particles->AddParticle(App->particles->HeavyExplosion, position.x + 30, position.y - 20, COLLIDER_NONE);
					App->particles->AddParticle(App->particles->LargeExplosion, position.x, position.y, COLLIDER_NONE);
					break;
				case 2:
				case 5:
				case 9:
					App->particles->AddParticle(App->particles->HeavyExplosion, position.x - 10, position.y - 10, COLLIDER_NONE);
					App->particles->AddParticle(App->particles->LightExplosion, position.x - 10, position.y + 10, COLLIDER_NONE);
					break;
				case 7:
				case 3:
				case 8:
					App->particles->AddParticle(App->particles->HeavyExplosion, position.x + 40, position.y + 10, COLLIDER_NONE);
					break;
				}
				estat++;
				current_time = SDL_GetTicks() + 500;
			}
		}
		if (estat == 10) {
			vida--;
			estat++;
		}
	}
	if (estat == -4) { // animacio inicial
		if (SDL_GetTicks() > current_time) {
			estat = -1;
			animation = &Base_Boss_Dreta;
			current_time = SDL_GetTicks() + 5000;
			capsBoss[0] = App->enemies->retornCap();
			capsBoss[1] = App->enemies->retornCap();
		}
	}
}

void Base_Boss::OnCollision(Collider* collider) {

}
void Base_Boss::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_boss6, position.x, position.y, &(animation->GetCurrentFrame()));
}