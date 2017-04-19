#include "Globals.h"
#include "Application.h"
#include "ModuleMenuScreen.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleBackGround2.h"
#include "ModuleBullets.h"
#include "ModulePlayer.h"
#include "ModuleMusic.h"
#include "Animation.h"
int i = 0;

ModuleMenuScreen::ModuleMenuScreen() {
	MenuScreenRect.x = 0;
	MenuScreenRect.y = 0;
	MenuScreenRect.w = 223;
	MenuScreenRect.h = 255;
	
	Main_Menu.PushBack({ 0,0,223,255 });
	Main_Menu.speed = 0.5f;
	Main_Menu.loop = false;

	Transition.PushBack({ 675,257,223,255 });
	Transition.PushBack({ 450,257,223,255 });
	Transition.PushBack({ 450,257,223,255 });
	Transition.PushBack({ 225,257,223,255 });
	Transition.PushBack({ 675,0,223,255 });
	Transition.PushBack({ 450,0,223,255 });
	Transition.PushBack({ 225,0,223,255 });
	Transition.PushBack({ 0,0,223,255 });
	Transition.PushBack({0,0,223,255});
	Transition.PushBack({ 225,0,223,255 });
	Transition.PushBack({ 450,0,223,255 });
	Transition.PushBack({ 675,0,223,255 });
	Transition.PushBack({ 0,257,223,255 });
	Transition.PushBack({ 225,257,223,255 });
	Transition.PushBack({ 450,257,223,255 });
	Transition.PushBack({ 675,257,223,255 });
	Transition.speed = 0.5f;
	Transition.loop = false;

}
ModuleMenuScreen::~ModuleMenuScreen() {}

bool ModuleMenuScreen::Start() {
	MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Start_Screen.png");
	App->menuScreen->Enable();
	selectorScreen(Start_Screen);
	current_animation = &Main_Menu;

	App->player->Disable();
	App->bullet->Disable();
	App->collision->Disable();
	App->render->MoveCameraToCenter();
	App->background->Disable();
	App->background2->Disable();

	return true;
}

bool ModuleMenuScreen::selectorScreen(MenuScreenNames name) {
	bool ret = true;
	switch (name) {
	case Players_Screen:
		App->player->Disable();
		App->bullet->Disable();
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Players_Screen.png");
		break;
	case Game_Over_Screen:
		App->player->Disable();
		App->bullet->Disable();
		App->render->MoveCameraToCenter();
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Continue_Screen.png");
		current_animation = &Main_Menu;
		App->music->CargarMusica(MUSICA_GAME_CONTINUE);
	break;
	}
	return ret;
}
update_status ModuleMenuScreen::Update() {
	App->render->CleanRender();
	App->render->Blit(MenuScreenTexture,59/*Aquest 59 s'ha de canviar per una funcio*/, 0, &MenuScreenRect);
	MenuScreenRect = current_animation->GetCurrentFrame();
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->menuScreen->Enable();
		App->menuScreen->selectorScreen(Players_Screen);
		i = 1;
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN && i == 1) {
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
		current_animation = &Transition;
		App->fade->FadeToBlack(this, App->background, 2.5f);
		App->player2->Disable();
		App->player2->jugador2Activat = false;
	}
	else if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN && i == 1) {
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
		current_animation = &Transition;
		App->fade->FadeToBlack(this, App->background, 2.5f);
		App->player2->Enable();
		App->player2->jugador2Activat = true;
	}

	return UPDATE_CONTINUE;
}

bool ModuleMenuScreen::CleanUp() {
	bool ret = true;
	App->textures->Unload(MenuScreenTexture);
	App->menuScreen->Disable();
	return ret;
}