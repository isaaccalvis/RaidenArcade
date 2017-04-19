#include "Globals.h"
#include "Application.h"
#include "ModuleBullets.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"

ModuleBullets::ModuleBullets() {}
ModuleBullets::~ModuleBullets(){}

bool ModuleBullets::Init() {
	powerUpLevelPlayer1 = 0;
	powerUpLevelPlayer2 = 0;
	App->bullet->Enable();
	return true;
}
update_status ModuleBullets::Update() {
	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_DOWN)
		powerUpLevelPlayer1++;
	else if (App->input->keyboard[SDL_SCANCODE_E] == KEY_DOWN)
		powerUpLevelPlayer1--;
	// BULLETS DEL JUGADOR 1
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->music->CargarFX(FX_DISPARAR);
		if (powerUpLevelPlayer1 == 0) {
			App->particles->bullet.life = 1000;
			iPoint vel(0, -4);
			App->particles->bullet.speed = vel;
			App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2) - 3/* 3 es l'amplada /2 de la bala */, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
		}
		else if (powerUpLevelPlayer1 == 1) {
			App->particles->bullet.life = 1000;
			iPoint vel(0, -4);
			App->particles->bullet.speed = vel;
			App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
		}
		else if (powerUpLevelPlayer1 == 2) {
			App->particles->bullet.life = 1000;
			iPoint vel(0, -4);
			iPoint velR(2, -4);
			iPoint velL(-2, -4);
			App->particles->bullet.speed = velL;
			App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
			App->particles->bullet.speed = vel;
			App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
			App->particles->bullet.speed = velR;
			App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
		}
	}

	// BULLETS DEL JUGADOR 2
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && App->player2->jugador2Activat == true) {
		App->particles->bullet.life = 2000;
		iPoint vel(0, -4);
		App->particles->bullet.speed = vel;
		App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5), App->player2->PROTA2.y - App->player2->PROTA2.h);
	}
	App->music->DescargarFX(FX_DISPARAR);

	return UPDATE_CONTINUE;
}
bool ModuleBullets::CleanUp() {
	return true;
}