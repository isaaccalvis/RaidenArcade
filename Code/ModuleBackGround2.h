#ifndef __ModuleBackground2_H__
#define __ModuleBackground2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground2 : public Module {
public:
	ModuleBackground2();
	~ModuleBackground2();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	Animation flag;
};

#endif