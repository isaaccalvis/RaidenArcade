#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include <iostream>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(){
	//position.x = 100;
	//position.y = 220;
	PROTA.x = SCREEN_WIDTH / 2;
	PROTA.y = SCREEN_HEIGHT / 2;
	PROTA.w = 26;
	PROTA.h = 30;

	idle.PushBack({83, 18, 26, 30});
	idle.speed = 0.2f;
	
	rightMov.PushBack({ 115,18,24,30 });

	leftMov.PushBack({ 52,18,24,30 });

}

ModulePlayer::~ModulePlayer(){}

bool ModulePlayer::Start(){
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Player/Players.png");
	return ret;
	App->player->Enable();
}

update_status ModulePlayer::Update(){
	Animation* current_animation = &idle;
	App->render->Blit(graphics, 0, -3265 + SCREEN_HEIGHT, &PROTA); // sea and sky

	int speed = 5;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1 && PROTA.x < (SCREEN_WIDTH - PROTA.w)){
		PROTA.x += speed;
		current_animation = &rightMov;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1 && PROTA.x > 0) {
		PROTA.x -= speed;
		current_animation = &leftMov;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1 && PROTA.y > PROTA.h) {
		PROTA.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1 && PROTA.y < SCREEN_HEIGHT) {
		PROTA.y += speed;
	}

	// CORRECTOR DE LIMITS
	if (PROTA.x < 0)
		PROTA.x = 0;
	if (PROTA.x > (SCREEN_WIDTH - PROTA.w))
		PROTA.x = SCREEN_WIDTH - PROTA.w;
	if (PROTA.y < PROTA.h)
		PROTA.y = PROTA.h;
	if (PROTA.y > SCREEN_HEIGHT)
		PROTA.y = SCREEN_HEIGHT;

	std::cout << App->render->camera.y  << " :: " << PROTA.y<< std::endl;
	std::cout << App->render->camera.x << " :: " << PROTA.x << std::endl;

	

		// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, PROTA.x, PROTA.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	bool ret = true;
	App->textures->Unload(graphics);

	return ret;
}