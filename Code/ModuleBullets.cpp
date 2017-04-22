#include "Globals.h"
#include "Application.h"
#include "ModuleBullets.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"

#define MAX_POWERUP 3
ModuleBullets::ModuleBullets() {}
ModuleBullets::~ModuleBullets(){}
iPoint vel(0, -4);
iPoint velR(1, -4);
iPoint velL(-1, -4);
bool ModuleBullets::Init() {
	powerUpLevelPlayer1 = 0;
	powerUpLevelPlayer2 = 0;
	App->bullet->Enable();
	return true;
}
update_status ModuleBullets::Update() {
	if (powerUpLevelPlayer1 < 0)
		powerUpLevelPlayer1 = 0;
	else if (powerUpLevelPlayer1 > MAX_POWERUP -1)
		powerUpLevelPlayer1 = MAX_POWERUP - 1;

	if (powerUpLevelPlayer2 < 0)
		powerUpLevelPlayer2 = 0;
	else if (powerUpLevelPlayer2 > MAX_POWERUP - 1)
		powerUpLevelPlayer2 = MAX_POWERUP - 1;

	if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_DOWN)
		powerUpLevelPlayer1++;
	else if (App->input->keyboard[SDL_SCANCODE_E] == KEY_DOWN)
		powerUpLevelPlayer1--;
	// BULLETS DEL JUGADOR 1
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->music->CargarFX(FX_DISPARAR);
		
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
		App->music->DescargarFX(FX_DISPARAR);
	}

	// BULLETS DEL JUGADOR 2
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {
		App->music->CargarFX(FX_DISPARAR);

		switch (powerUpLevelPlayer2) {
		case 0:
			App->particles->bullet.life = 1000;
			App->particles->bullet.speed = vel;
			App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2) - 3/* 3 es l'amplada /2 de la bala */, App->player2->PROTA2.y, COLLIDER_PLAYER_SHOT);
			break;
		case 1:
			App->particles->bullet.life = 1000;
			App->particles->bullet.speed = vel;
			App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) + 6, App->player2->PROTA2.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) - 6, App->player2->PROTA2.y, COLLIDER_PLAYER_SHOT);
			break;
		case 2:
			App->particles->bullet.life = 1000;
			App->particles->bullet.speed = velL;
			App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) - 2, App->player2->PROTA2.y, COLLIDER_PLAYER_SHOT);
			App->particles->bullet.speed = vel;
			App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) + 0, App->player2->PROTA2.y, COLLIDER_PLAYER_SHOT);
			App->particles->bullet.speed = velR;
			App->particles->AddParticle(App->particles->bullet, App->player2->PROTA2.x + (App->player2->PROTA2.w / 2.5) + 2, App->player2->PROTA2.y, COLLIDER_PLAYER_SHOT);
			break;
		}
		App->music->DescargarFX(FX_DISPARAR);
	}

	return UPDATE_CONTINUE;
}
bool ModuleBullets::CleanUp() {
	return true;
}