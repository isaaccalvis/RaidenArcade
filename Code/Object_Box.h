#ifndef __Object_Box_H__
#define __Object_Box_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Object_Box : public Enemy {
private:
	//int original_y = 0;
	Animation Object_Box_Animation;

public:
	Object_Box(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void Draw(/*SDL_Texture* sprites*/);
};
#endif