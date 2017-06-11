#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleBackground.h"
#include "ModuleMenuScreen.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender() : Module(){
	camera.x = -(SCREEN_WIDTH / 2);
	camera.y = 0;
	camera.w = ORIGINAL_CAMERA_WEIGHT;
	camera.h = ORIGINAL_CAMERA_HEIGHT;
}

ModuleRender::~ModuleRender(){}

bool ModuleRender::Init(){
	bool ret = true;
	Uint32 flags = 0;
	if(REN_VSYNC == true){
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}
	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	if(renderer == NULL){
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	return ret;
}

update_status ModuleRender::PreUpdate(){
	SDL_RenderClear(renderer);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {
	if (App->menuScreen->IsEnabled() == false) {
		int speed = 3;
		if (App->player2->IsEnabled() == true) {
			if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
				if (App->player2->distanciaPlayers > -198)
					if (camera.x < 0)
						camera.x += speed;
			if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft2 == KEY_STATE::KEY_REPEAT || App->input->joy_left2 == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
				if (App->player2->distanciaPlayers < 198)
					if (camera.x < 0)
						camera.x += speed;
			if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
				if (App->player2->distanciaPlayers < 198)
					if ((camera.x - camera.w) > -SCREEN_WIDTH * 3)
						camera.x -= speed;
			if (((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->dpadRight2 == KEY_STATE::KEY_REPEAT || App->input->joy_right2 == KEY_STATE::KEY_REPEAT)) && (App->player->potMoure == true || App->player2->potMoure2 == true))
				if (App->player2->distanciaPlayers > -198)
					if ((camera.x - camera.w) > -SCREEN_WIDTH * 3)
						camera.x -= speed;
		}
		else {
			if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) && App->player->potMoure == true)
				if (camera.x < 0)
					camera.x += speed;

			if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT) && App->player->potMoure == true)
				if ((camera.x - camera.w) > -SCREEN_WIDTH * 3)
					camera.x -= speed;
		}
		if (camera.x > 0)
			camera.x = 0;
		if ((camera.x - camera.w) > SCREEN_WIDTH)
			camera.x = SCREEN_WIDTH - ORIGINAL_CAMERA_WEIGHT;
	}
	else {
		MoveCameraToCenter();
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate(){
	SDL_RenderSetLogicalSize(renderer, 700, 760);
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp(){
	if(renderer != NULL){
		SDL_DestroyRenderer(renderer);
	}
	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed){
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if(section != NULL){
		rect.w = section->w;
		rect.h = section->h;
	}else{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0){
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}
	return ret;
}

bool ModuleRender::fBlit(SDL_Texture* texture, float x, float y, SDL_Rect* section, float speed) {
	bool ret = true;
	SDL_Rect rect;
	rect.x = (camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (camera.y * speed) + y * SCREEN_SIZE;

	if (section != NULL) {
		rect.w = section->w;
		rect.h = section->h;
	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0) {
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}
	return ret;
}

bool ModuleRender::CleanRender() {
	bool ret = true;
	SDL_RenderClear(App->render->renderer);

	return ret;
}
bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera){
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera){
		rec.x = (camera.x) + rect.x * SCREEN_SIZE;
		rec.y = (camera.y) + rect.y * SCREEN_SIZE;
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}
	if (SDL_RenderFillRect(renderer, &rec) != 0){
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}
	return ret;
}

void ModuleRender::MoveCameraToCenter() {
	camera.x = -(SCREEN_WIDTH / 2);
	camera.y = 0;
	camera.w = ORIGINAL_CAMERA_WEIGHT;
	camera.h = ORIGINAL_CAMERA_HEIGHT;
}