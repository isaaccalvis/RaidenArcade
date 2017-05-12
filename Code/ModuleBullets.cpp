#include "Globals.h"
#include "Application.h"
#include "ModuleBullets.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_timer.h"

#define MAX_POWERUP 8
ModuleBullets::ModuleBullets() {}
ModuleBullets::~ModuleBullets(){}
iPoint vel(0, -8);
iPoint velR(1, -7);
iPoint velR2(2, -6);
iPoint velR3(3, -5);
iPoint velL(-1, -7);
iPoint velL2(-2, -6);
iPoint velL3(-3, -5);
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
	else if (App->input->keyboard[SDL_SCANCODE_R] == KEY_DOWN && App->player->GodMode == true)
		if (powerUpTypePlayer1 == Vulkan)
			powerUpTypePlayer1 = Laser;
		else if (powerUpTypePlayer1 == Laser)
			powerUpTypePlayer1 = Vulkan;
	// BULLETS DEL JUGADOR 1
	if ((App->player->destroyed == false && App->player->potMoure == true) && App->player->IsEnabled() == true) {
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
			if (powerUpTypePlayer1 == Vulkan) {
				App->music->PlayFX(shoot);
				switch (powerUpLevelPlayer1) {
				case 0:
					App->particles->bullet.speed = vel;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2) - 3/* 3 es l'amplada /2 de la bala */, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 1:
					App->particles->bullet.speed = vel;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 6, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 6, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 2:
					App->particles->bullet.speed = velL;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = vel;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 0, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velR;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 3:
					App->particles->bullet3.speed = velL;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet3.speed = vel;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 0 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet3.speed = velR;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 4:
					App->particles->bullet.speed = velL;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velL2;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = vel;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 0 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velR;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velR2;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 5:
					App->particles->bullet3.speed = velL;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet3.speed = velL2;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet3.speed = vel;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 0 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet3.speed = velR;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet3.speed = velR2;
					App->particles->AddParticle(App->particles->bullet3, App->player->PROTA.x + (App->player->PROTA.w / 2.5) + 2 - 3, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 6:
					App->particles->bullet.speed = velL;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velL2;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = vel;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velR;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = velR2;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				case 7:
					App->particles->bulletL.speed = velL;
					App->particles->AddParticle(App->particles->bulletL, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bulletL.speed = velL2;
					App->particles->AddParticle(App->particles->bulletL, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bulletL.speed = velL3;
					App->particles->AddParticle(App->particles->bulletL, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bullet.speed = vel;
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 - 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bullet, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bulletR.speed = velR;
					App->particles->AddParticle(App->particles->bulletR, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bulletR.speed = velR2;
					App->particles->AddParticle(App->particles->bulletR, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					App->particles->bulletR.speed = velR3;
					App->particles->AddParticle(App->particles->bulletR, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 4 + 4, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
					break;
				}
			}
			else if (powerUpTypePlayer1 == Laser) {
				if (SDL_GetTicks() >= esperaShootP1) {
					switch (powerUpLevelPlayer1) {
					case 0:
						desfaseSpriteDispar = 2;
						App->particles->laserLight.speed = vel;
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						break;
					case 1:
						desfaseSpriteDispar = 2;
						App->particles->laserLight.speed = vel;
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserLight, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						break;
					case 2:
						desfaseSpriteDispar = 7;
						App->particles->laserHeavy2s.speed = vel;
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						break;
					case 3:
						App->particles->laserHeavy2s.speed = vel;
						App->particles->laserHeavy3s.speed = vel;
						desfaseSpriteDispar = 7;
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						desfaseSpriteDispar = 6;
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						break;
					case 4:
						App->particles->laserHeavy3s.speed = vel;
						desfaseSpriteDispar = 6;
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						break;
					case 5:
						App->particles->laserHeavy3s.speed = vel;
						App->particles->laserHeavy2s.speed = vel;
						desfaseSpriteDispar = 15;
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						desfaseSpriteDispar = -5;
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						desfaseSpriteDispar = 6;
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserHeavy3s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						break;
					case 6:
						App->particles->laserHeavy2s.speed = vel;
						desfaseSpriteDispar = 15;
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						desfaseSpriteDispar = -5;
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 50);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 100);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 150);
						App->particles->AddParticle(App->particles->laserHeavy2s, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 200);
						break;
					case 7:
						App->particles->LaserBeamHeavy.speed = vel;
						desfaseSpriteDispar = 7;
						App->particles->AddParticle(App->particles->LaserBeamHeavy, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->LaserBeamHeavy, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 30);
						App->particles->AddParticle(App->particles->LaserBeamHeavy, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 60);
						App->particles->AddParticle(App->particles->LaserBeamHeavy, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 90);
						App->particles->AddParticle(App->particles->LaserBeamHeavy, App->player->PROTA.x + (App->player->PROTA.w / 2) - desfaseSpriteDispar, App->player->PROTA.y, COLLIDER_PLAYER_SHOT, 120);
						break;
					}
					if (powerUpLevelPlayer1 < 7)
						esperaShootP1 = SDL_GetTicks() + 200;
					else
						esperaShootP1 = SDL_GetTicks() + 50;

				}
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN && postXYbomb[2] <= SDL_GetTicks() && (App->player->destroyed == false && App->player->potMoure == true) && App->player->IsEnabled() == true) {
		bombOnPlayer1 = true;
		postXYbomb[2] = SDL_GetTicks() + 3000;
		current_time = SDL_GetTicks() + 500;
		App->particles->preBomb.life = 500;
		App->particles->preBomb.anim.speed = 0.2f;
		App->particles->preBomb.speed = velNull;
		App->particles->AddParticle(App->particles->preBomb, App->player->PROTA.x + (App->player->PROTA.w / 2.5) - 2, App->player->PROTA.y - 30, COLLIDER_NONE);
		postXYbomb[0] = App->player->PROTA.x;
		postXYbomb[1] = App->player->PROTA.y;
	}
	if (bombOnPlayer1 == true) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
			App->particles->bomb.life = 1000;
			App->particles->bomb.speed = velNull;
			App->particles->AddParticle(App->particles->bomb,postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_NONE);
			current_time = SDL_GetTicks() + 1000;
			bombOnPlayer1 = false;
			postXYbomb[3] = 1;
		}
	}
	if (current_time > SDL_GetTicks()) {
		if ((current_time - SDL_GetTicks()) < 100 && postXYbomb[3] == 10) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 200 && postXYbomb[3] == 9) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 300 && postXYbomb[3] == 8) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 400 && postXYbomb[3] == 7) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 500 && postXYbomb[3] == 6) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 600 && postXYbomb[3] == 5) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 700 && postXYbomb[3] == 4) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 800 && postXYbomb[3] == 3) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 900 && postXYbomb[3] == 2) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
		else if ((current_time - SDL_GetTicks()) < 999 && postXYbomb[3] == 1) {
			App->particles->AddParticle(App->particles->bombFantasma, postXYbomb[0] + (App->player->PROTA.w / 2.5) - 84, postXYbomb[1] - 100, COLLIDER_PLAYER_SHOT);
			postXYbomb[3]++;
		}
	}

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