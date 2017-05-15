#ifndef __HeavyTurret_H__
#define __HeavyTurret_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class HeavyTurret : public Enemy {
private:
	Animation HeavyTurret_Animation;
	int current_time;
	bool dispara;
public:
	HeavyTurret(int x, int y);
	~HeavyTurret(){}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif