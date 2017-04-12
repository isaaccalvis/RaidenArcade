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

#define MAP_HEIGHT 3265

int posBackGround = -MAP_HEIGHT;
int speedBackGround = 2;

ModuleBackground::ModuleBackground(){
	ground.x = 352;
	ground.y = 5;
	ground.w = 353;
	ground.h = 3265;

	background.x = 0;
	background.y = -1;
	background.w = 352;
	background.h = MAP_HEIGHT;

	PosCow1.x = 100;
	PosCow1.y = 2210;

	cow1.PushBack({ 24,26,48,25 });
	cow1.PushBack({ 77,26,48,25 });
	cow1.speed = 0.02;

	PosCow2.x = 250;
	PosCow2.y = 2223;

	cow2.PushBack({ 24, 68, 25, 35 });
	cow2.PushBack({ 56, 68, 25, 35 });
	cow2.PushBack({ 89, 68, 25, 35 });
	cow2.speed = 0.03;

	PosCow3.x = 270;
	PosCow3.y = 2223;

	cow3.PushBack({ 24, 114, 36, 32 });
	cow3.PushBack({ 69, 114, 36, 32 });
	cow3.speed = 0.04;

	PosCow4.x = 100;
	PosCow4.y = 2139;

	cow4.PushBack({ 22, 160, 70, 52 });
	cow4.PushBack({ 106, 160, 68, 52 });
	cow4.speed = 0.02;
}

ModuleBackground::~ModuleBackground(){}

bool ModuleBackground::Start(){

	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Sprites/TileMaps/Nivel_1_Tilemap.png");
	
	cows = App->textures->Load("Sprites/Extras/Cows.png");

	App->music->CargarMusica(MUSICA_NIVEL_1);

	App->background->Enable();
	return ret;
}

update_status ModuleBackground::Update(){
	App->render->CleanRender();
	App->render->Blit(graphics, 0, posBackGround + SCREEN_HEIGHT, &background);
	App->render->Blit(graphics, 0, posBackGround + SCREEN_HEIGHT, &ground);
	posBackGround += speedBackGround;

	Animation* current_animation = &cow1;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(cows, PosCow1.x, posBackGround + PosCow1.y, &r);

	Animation* current_animation2 = &cow2;
	SDL_Rect r2 = current_animation2->GetCurrentFrame();
	App->render->Blit(cows, PosCow2.x, posBackGround + PosCow2.y, &r2);

	Animation* current_animation3 = &cow3;
	SDL_Rect r3 = current_animation3->GetCurrentFrame();
	App->render->Blit(cows, PosCow3.x, posBackGround + PosCow3.y, &r3);

	Animation* current_animation4 = &cow4;
	SDL_Rect r4 = current_animation4->GetCurrentFrame();
	App->render->Blit(cows, PosCow4.x, posBackGround + PosCow4.y, &r4);

	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, App->background2, 1);
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_STATE::KEY_DOWN) {
		App->background->Disable();
		App->background2->Disable();
		App->menuScreen->Enable();
		App->menuScreen->selectorScreen(GameOverScreen);
	}

	return UPDATE_CONTINUE;
}


bool ModuleBackground::CleanUp() {
	bool ret = true;
	App->textures->Unload(graphics);
	App->textures->Unload(cows);
	App->background->Disable();
	return ret;
}