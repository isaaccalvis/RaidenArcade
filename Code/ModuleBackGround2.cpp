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

#define MAP_HEIGHT 4998

int posBackGround2 = -MAP_HEIGHT;
int speedBackGround2 = 2;

ModuleBackground2::ModuleBackground2(){
	ground.x = 352;
	ground.y = 0;
	ground.w = 352;
	ground.h = MAP_HEIGHT;

	background.x = 0;
	background.y = 0;
	background.w = 352;
	background.h = MAP_HEIGHT;

	// Aqui van lo de les animations flag.pushBack({x,y,w,h})

}

ModuleBackground2::~ModuleBackground2() {}

bool ModuleBackground2::Start() {	
	LOG("Loading background assets");
	bool ret = true;
	posBackGround2 = -MAP_HEIGHT;
	graphics2 = App->textures->Load("Sprites/TileMaps/Nivel_2_Tilemap.png");	
	App->background2->Enable();
	App->music->LoadMusic("Audio/Music/Stage_2-7.ogg");

	return ret;
}

update_status ModuleBackground2::Update() {
	App->render->CleanRender();
	App->render->Blit(graphics2, 0, posBackGround2 + SCREEN_HEIGHT, &background);
	App->render->Blit(graphics2, 0, posBackGround2 + SCREEN_HEIGHT, &ground);
	posBackGround2 += speedBackGround2;

	if (App->input->keyboard[SDL_SCANCODE_9] == 1) {
		App->fade->FadeToBlack(this, App->background, 1);
		App->background2->CleanUp();
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_STATE::KEY_DOWN) {
		App->background->CleanUp();
		App->background2->CleanUp();
		App->menuScreen->Enable();
		App->menuScreen->selectorScreen(Game_Over_Screen);
		//App->menuScreen->current_animation = App->menuScreen->;
		//&pantallaIniciAnimStatic
	}

	return UPDATE_CONTINUE;
}


bool ModuleBackground2::CleanUp() {
	bool ret = true;
	App->textures->Unload(graphics2);
	App->background2->Disable();
	return ret;
}