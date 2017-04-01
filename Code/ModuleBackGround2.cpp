#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "ModuleBackground2.h"
#include "ModuleFadeToBlack.h"

#define MAP_HEIGHT 4998

int posBackGround2 = -MAP_HEIGHT;
int speedBackGround2 = 2;

ModuleBackground2::ModuleBackground2()
{
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
	graphics2 = App->textures->Load("Nivel_2_Tilemap.png");
	
	App->background2->Enable();

	return ret;
}

update_status ModuleBackground2::Update() {
	App->render->CleanRender();
	App->render->Blit(graphics2, 0, posBackGround2 + SCREEN_HEIGHT, &background);
	App->render->Blit(graphics2, 0, posBackGround2 + SCREEN_HEIGHT, &ground);
	posBackGround2 += speedBackGround2;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(this, App->background, 1);
	}

	return UPDATE_CONTINUE;
}


bool ModuleBackground2::CleanUp() {
	
	App->background2->Disable();
	return true;
}