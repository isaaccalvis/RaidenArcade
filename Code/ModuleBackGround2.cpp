#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground2.h"

#define MAP_HEIGHT 4998

int posBackGround2 = -MAP_HEIGHT;
int speedBackGround2 = 2;

ModuleBackground2::ModuleBackground2()
{
	ground.x = 351;
	ground.y = 0;
	ground.w = 351;
	ground.h = MAP_HEIGHT;

	background.x = 0;
	background.y = 0;
	background.w = 351;
	background.h = MAP_HEIGHT;

	// Aqui van lo de les animations flag.pushBack({x,y,w,h})

}

ModuleBackground2::~ModuleBackground2() {}

bool ModuleBackground2::Start() {
	App->background2->Disable();
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Nivel_2_Tilemap.png");
	return ret;
}

update_status ModuleBackground2::Update() {
	App->render->CleanRender();
	App->render->Blit(graphics, 0, posBackGround2 + SCREEN_HEIGHT, &background);
	App->render->Blit(graphics, 0, posBackGround2 + SCREEN_HEIGHT, &ground);
	posBackGround2 += speedBackGround2;
	return UPDATE_CONTINUE;
}