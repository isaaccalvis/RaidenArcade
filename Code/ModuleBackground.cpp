#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "ModuleBackground2.h"
#include "ModuleFadeToBlack.h"

#define MAP_HEIGHT 3265

int posBackGround = -MAP_HEIGHT;
int speedBackGround = 2;

ModuleBackground::ModuleBackground()
{
	ground.x = 352;
	ground.y = 0;
	ground.w = 352;
	ground.h = 3265;

	background.x = 0;
	background.y = 0;
	background.w = 352;
	background.h = MAP_HEIGHT;

	// Aqui van lo de les animations flag.pushBack({x,y,w,h})
	
}

ModuleBackground::~ModuleBackground(){}

bool ModuleBackground::Start(){

	LOG("Loading background assets");	
	bool ret = true;
	graphics = App->textures->Load("Sprites/TileMaps/Nivel_1_Tilemap.png");
	
	App->background->Enable();
	return ret;
}

update_status ModuleBackground::Update(){
	App->render->CleanRender();
	App->render->Blit(graphics, 0, posBackGround + SCREEN_HEIGHT, &background);
	App->render->Blit(graphics, 0, posBackGround + SCREEN_HEIGHT, &ground);
	posBackGround += speedBackGround;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->background2, 1);
	}

	return UPDATE_CONTINUE;
}


bool ModuleBackground::CleanUp() {
	
	App->background->Disable();
	return true;
}