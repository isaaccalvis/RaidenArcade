#ifndef __Object_PowerUp_H__
#define __Object_PowerUp_H__

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "Path.h"

enum powerUp_State {
	Red,
	Blue
};

class Object_PowerUp : public Enemy {
private:
	Animation Object_PowerUp_Animation;
	Animation Object_PowerUp_Animation_Red;
	Animation Object_PowerUp_Animation_Blue;

	int current_time;
	powerUp_State powerUpState;
	Path path;
	fPoint original_pos;

public:
	Object_PowerUp(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown(/*SDL_Texture* sprites*/);
};
#endif