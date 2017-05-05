#ifndef __Object_Medal_H__
#define __Object_Medal_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Object_Medal : public Enemy {
private:
	//int original_y = 0;
	Animation Object_Medal_Animation;

public:
	Object_Medal(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown(/*SDL_Texture* sprites*/);
};
#endif