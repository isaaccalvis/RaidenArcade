#ifndef __Asteroid_H__
#define __Asteroid_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Asteroid : public Enemy {
private:
	Animation Asteroid_Animation;
	int current_time;
	bool dispara;
public:
	Asteroid(int x, int y);
	~Asteroid(){}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif