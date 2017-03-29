#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

#define MAP_HEIGHT 3265

int posBackGround = -MAP_HEIGHT;
int speedBackGround = 2;

ModuleBackground::ModuleBackground()
{
	ground.x = 351;
	ground.y = 0;
	ground.w = 351;
	ground.h = 3265;

	background.x = 0;
	background.y = 0;
	background.w = 351;
	background.h = MAP_HEIGHT;

	// Aqui van lo de les animations flag.pushBack({x,y,w,h})
	
}

ModuleBackground::~ModuleBackground(){}

bool ModuleBackground::Start(){
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Nivel_1_Tilemap.png");
	return ret;
}

update_status ModuleBackground::Update(){
	App->render->CleanRender();
	App->render->Blit(graphics, 0, posBackGround + SCREEN_HEIGHT, &background);
	App->render->Blit(graphics, 0, posBackGround + SCREEN_HEIGHT, &ground);
	posBackGround += speedBackGround;
	return UPDATE_CONTINUE;
}