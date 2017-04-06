#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleBackground.h"
#include "ModuleBackGround2.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleMusic.h"
#include "ModuleCollider.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenuScreen.h"
#include "ModuleParticles.h"
#include "ModuleBullets.h"

Application::Application(){
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = background = new ModuleBackground();
	modules[5] = background2 = new ModuleBackground2();
	modules[6] = player = new ModulePlayer();
	modules[7] = player2 = new ModulePlayer2();
	modules[8] = music = new ModuleMusic();
	modules[9] = collider = new ModuleCollider();	
	modules[10] = particles = new ModuleParticles();
	modules[11] = fade = new ModuleFadeToBlack();
	modules[12] = menuScreen = new ModuleMenuScreen();
	modules[13] = bullet = new ModuleBullets();
}

Application::~Application(){
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init(){
	bool ret = true;

	//We put here all the modules we don't want to inicialite first
	background2->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update(){
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp(){
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}