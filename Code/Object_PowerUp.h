#ifndef __Object_PowerUp_H__
#define __Object_PowerUp_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Object_PowerUp : public Enemy {
private:
	//int original_y = 0;
	Animation Object_PowerUp_Animation;

public:
	Object_PowerUp(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void Draw(/*SDL_Texture* sprites*/);
};
#endif