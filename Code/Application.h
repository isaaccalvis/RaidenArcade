#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 15

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleBackground;
class ModulePlayer;
class ModulePlayer2;
class ModuleMusic;
class ModuleCollision;
class ModuleFadeToBlack;
class ModuleMenuScreen;
class ModuleParticles;
class ModuleBullets;
class ModuleEnemies;
class ModuleFonts;
class Module;

class Application{
public:
	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleBackground* background;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleMusic* music;
	ModuleCollision* collision;
	ModuleFadeToBlack* fade;
	ModuleMenuScreen* menuScreen;
	ModuleParticles* particles;
	ModuleBullets* bullet;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;

public:
	
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif