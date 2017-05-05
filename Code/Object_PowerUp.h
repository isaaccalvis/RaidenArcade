#ifndef __Object_PowerUp_H__
#define __Object_PowerUp_H__

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "Path.h"

class Object_PowerUp : public Enemy {
private:
	Animation Object_PowerUp_Animation;

	Path path;
	fPoint original_pos;

public:
	Object_PowerUp(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown(/*SDL_Texture* sprites*/);
};
#endif