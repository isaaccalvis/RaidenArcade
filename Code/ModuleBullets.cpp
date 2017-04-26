#include "Globals.h"
#include "Application.h"
#include "ModuleBullets.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "SDL\include\SDL_timer.h"

#define MAX_POWERUP 3
ModuleBullets::ModuleBullets() {}
ModuleBullets::~ModuleBullets(){}
iPoint vel(0, -6);
iPoint velR(1, -6);
iPoint velL(-1, -6);
iPoint velNull(0, 0);

uint shoot;

bool ModuleBullets::Start() {
	shoot = App->music->LoadFX("Audio/Fx/Shot_1(bullet).wav");
	return true;
}

bool ModuleBullets::Init() {
	powerUpLevelPlayer1 = 0;
	powerUpLevelPlayer2 = 0;
	App->bullet->Enable();
	return true;
}
update_status ModuleBullets::Update() {
	if (powerUpLevelPlayer1 < 0)
		powerUpLevelPlayer1 = 0;
	else if (powerUpLevelPlayer1 > MAX_POWERUP - 1)
		powerUpLevelPlayer1 = MAX_POWERUP - 1;

	if (powerUpLevelPlayer2 < 0)
		powerUpLevelPlayer2 = 0;
	else if (powerUpLevelPlayer2 > MAX_POWERUP - 1)
		powerUpLevelPlayer2 = MAX_POWERUP - 1;

	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_DOWN && App->player->GodMode == true)
		powerUpLevelPlayer1++;
	else if (App->input->keyboard[SDL_SCANCODE_E] == KEY_DOWN && App->player->GodMode == true)
		powerUpLevelPlayer1--;
	// BULLETS DEL JUGADOR 1
	if ((App->player->destroyed == false && App->player->potMoure == true) && App->player->IsEnabled() == true) {
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			App->music->PlayFX(shoot);
			switch (powerUpLevelPlayer1) {
			case 0:
				App->particles->bullet.life = 1000;
				App->particles->bullet.speed = vel;
				App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2) - 3/* 3 es l'amplada /2 de la bala */, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
				break;
			case 1:
				App->particles->bullet.life = 1000;
				App->particles->bullet.speed = vel;
				App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 6, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 6, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
				break;
			case 2:
				App->particles->bullet.life = 1000;
				App->particles->bullet.speed = velL;
				App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
				App->particles->bullet.speed = vel;
				App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 0, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
				App->particles->bullet.speed = velR;
				App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
				break;
			}
		}
	}


	//if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN) {
	//	bombOn = true;
	//	current_time = SDL_GetTicks() + 400;
	//}
	//if (bombOn == true) {
	//	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
	//		App->particles->bomb.life = 500;
	//		App->particles->bomb.speed = velNull;
	//		App->particles->AddParticle(App->particles->bomb, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
	//		bombOn = false;
	//	}
	//}


	// BULLETS DEL JUGADOR 2
	if (App->player2->destroyed == false && App->player2->potMoure2 == true && App->player2->IsEnabled() == true) {
		if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && App->player2->IsEnabled()) {
			App->music->PlayFX(shoot);

			switch (powerUpLevelPlayer2) {
			case 0:
				App->particles->bullet.life = 1000;
				App->particles->bullet.speed = vel;
				App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2) - 3/* 3 es l'amplada /2 de la bala */, App->player2->PROTA2.y, COLLIDER_PLAYER2_SHOT);
				break;
			case 1:
				App->particles->bullet.life = 1000;
				App->particles->bullet.speed = vel;
				App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) + 6, App->player2->PROTA2.y, COLLIDER_PLAYER2_SHOT);
				App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) - 6, App->player2->PROTA2.y, COLLIDER_PLAYER2_SHOT);
				break;
			case 2:
				App->particles->bullet.life = 1000;
				App->particles->bullet.speed = velL;
				App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) - 2, App->player2->PROTA2.y, COLLIDER_PLAYER2_SHOT);
				App->particles->bullet.speed = vel;
				App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) + 0, App->player2->PROTA2.y, COLLIDER_PLAYER2_SHOT);
				App->particles->bullet.speed = velR;
				App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) + 2, App->player2->PROTA2.y, COLLIDER_PLAYER2_SHOT);
				break;
			}
		}
	}
	return UPDATE_CONTINUE;
}
bool ModuleBullets::CleanUp() {
	return true;
}