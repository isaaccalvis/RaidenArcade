#include "Globals.h"
#include "Application.h"
#include "ModuleMenuScreen.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "Animation.h"


ModuleMenuScreen::ModuleMenuScreen() {
	MenuScreenRect.x = 0;
	MenuScreenRect.y = 0;
	MenuScreenRect.w = 223;
	MenuScreenRect.h = 255;
	/*
	pantallaIniciAnimStatic.PushBack({ 0,0,223,255 });
	pantallaIniciAnimStatic.speed = 0.5f;*/

	pantallaIniciAnim.PushBack({0,0,223,255});
	pantallaIniciAnim.PushBack({ 225,0,223,255 });
	pantallaIniciAnim.PushBack({ 450,0,223,255 });
	pantallaIniciAnim.PushBack({ 675,0,223,255 });
	pantallaIniciAnim.PushBack({ 0,257,223,255 });
	pantallaIniciAnim.PushBack({ 225,257,223,255 });
	pantallaIniciAnim.PushBack({ 450,257,223,255 });
	pantallaIniciAnim.speed = 0.1f;

}
ModuleMenuScreen::~ModuleMenuScreen() {}

bool ModuleMenuScreen::Start() {
	MenuScreenTexture = App->textures->Load("Loading_Screen.png");
	App->menuScreen->Enable();
	return true;
}

bool ModuleMenuScreen::selectorScreen(MenuScreenNames name) {
	switch (name) {
	case StartScreen:
		MenuScreenTexture = App->textures->Load("Loading_Screen.png");
		App->menuScreen->Enable();
	break;
	case GameOverScreen:
		//MenuScreenTexture = App->textures->Load("");
		App->menuScreen->Enable();
	break;
	}
	return true;
}

update_status ModuleMenuScreen::Update() {
	Animation* 	current_animation =/* &pantallaIniciAnimStatic*/ &pantallaIniciAnim;
	App->render->CleanRender();
	App->render->Blit(MenuScreenTexture, 0, 0, &MenuScreenRect);
	MenuScreenRect = current_animation->GetCurrentFrame();
	if (App->input->keyboard[SDL_SCANCODE_P] == 1) {
		//current_animation = &pantallaIniciAnim;
		App->fade->FadeToBlack(this, App->background, 1);
	}

	return UPDATE_CONTINUE;
}

bool ModuleMenuScreen::CleanUp() {
	App->menuScreen->Disable();
	return true;
}