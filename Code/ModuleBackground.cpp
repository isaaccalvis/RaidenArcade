#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "ModuleBackground2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenuScreen.h"
#include "ModuleMusic.h"
#include "p2Point.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleBullets.h"
#include "ModuleFonts.h"

#include "SDL\include\SDL_timer.h"
#define MAP_HEIGHT 5850

ModuleBackground::ModuleBackground(){
	ground.x = 352;
	ground.y = 0;
	ground.w = 352;
	ground.h = MAP_HEIGHT;// MAP_HEIGHT;

	background.x = 0;
	background.y = 0;
	background.w = 352;
	background.h = MAP_HEIGHT;

	ship.x = 420;
	ship.y = 6075;
	ship.w = 225;
	ship.h = 512;
}

ModuleBackground::~ModuleBackground(){}

bool ModuleBackground::Start(){
	bool ret = true;
	current_time = SDL_GetTicks() + 5000;
	posBackGround = -MAP_HEIGHT /*- ORIGINAL_CAMERA_HEIGHT*/;
	posShipIncial = 0;
	speedBackGround = 0.3f;
	controlador_Auxiliar_Background_1 = true;
	controlador_spawn_LightShooter = 0;
	controlador_spawn_BonusPlane = 0;
	controlador_spawn_box = 0;
	controlador_spawn_Turret = 0;

	graphics = App->textures->Load("Sprites/TileMaps/Nivel_6_Tilemap.png");
	App->music->LoadMusic("Audio/Music/Stage_1-4.ogg");
	return ret;
}

update_status ModuleBackground::Update() {
	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
		if (controlador_Auxiliar_Background_1 == true) {
			if (App->player->potMoure == false) {
				App->player->potMoure = true;
				App->bullet->Enable();
			}
			if (App->player2->potMoure2 == false) {
				App->player2->potMoure2 = true;
			}
			controlador_Auxiliar_Background_1 = false;
		}
		App->render->CleanRender();
		App->render->fBlit(graphics, 0, posBackGround + SCREEN_HEIGHT, &background);
		App->render->fBlit(graphics, 0, posBackGround + SCREEN_HEIGHT, &ground);
		if (posBackGround < -265)
			posBackGround += speedBackGround;
		else { // Animacio del prota pirant del mapa
			posBackGround = -265;
			App->player->GodMode = true;
			if (App->player->IsEnabled() == true) {
				App->player->potMoure = false;
				App->player->PROTA.y--;
			}
			if (App->player2->IsEnabled() == true) {
				App->player2->potMoure2 = false;
				App->player2->PROTA2.y--;
			}
			if (App->player->PROTA.y <= 0) {
				App->menuScreen->Enable();
				App->menuScreen->CridaMenu();
			}
		}
	}
	else {
		App->bullet->Disable();
		App->render->CleanRender();
		App->player->potMoure = false;
		App->player2->potMoure2 = false;
		App->render->fBlit(graphics, 0, SCREEN_HEIGHT - MAP_HEIGHT, &background);
		App->render->fBlit(graphics, 0, SCREEN_HEIGHT - MAP_HEIGHT, &ground);
		App->render->fBlit(graphics, 0, posShipIncial, &ship);
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 350)) {
			posShipIncial += 2;
			App->player->current_animation = &(App->player->Despegar3);
			App->player2->current_animation = &(App->player2->Despegar3);
		}
		else if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 4000)) {
			App->player->current_animation = &(App->player->Despegar2);
			App->player2->current_animation = &(App->player2->Despegar2);
			posShipIncial += 1;
		}
		else {
			posShipIncial += 0;
			App->player->current_animation = &(App->player->Despegar1);
			App->player2->current_animation = &(App->player2->Despegar1);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_STATE::KEY_DOWN && App->player->GodMode == true) {		
		App->fade->FadeToBlack(this, App->background2, 1);
		App->background->CleanUp();
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_STATE::KEY_DOWN && App->player->GodMode == true) {
		App->background->CleanUp();
		App->background2->CleanUp();
		App->player->CleanUp();
		App->player2->CleanUp();
		App->enemies->CleanUp();
		App->menuScreen->Enable();
		App->menuScreen->CridaMenu();
	
	}
	return UPDATE_CONTINUE;
}

void ModuleBackground::CridaScoreGeneral() {
	App->fonts->BlitText(180, 10, App->player->font_score, "hi-score");
	char str[10];
	if (App->player->puntuacioP1 > App->player2->puntuacioP2)
		sprintf_s(str, "%i", App->player->puntuacioP1);
	else
		sprintf_s(str, "%i", App->player2->puntuacioP2);
	App->fonts->BlitText(200, 25, App->player->font_score, str);
	sprintf_s(App->player->score_text, 10, "%7d", App->player->puntuacioP1);
}

bool ModuleBackground::CleanUp() {
	bool ret = true;
	App->textures->Unload(graphics);
	App->background->Disable();
	App->music->UnloadMusic();
	App->fonts->UnLoad(App->player->font_score);

	return ret;
}