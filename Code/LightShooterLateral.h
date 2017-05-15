#ifndef __LightShooterLateral_H__
#define __LightShooterLateral_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class LightShooterLateral : public Enemy {
private:
	Animation LightShooterLateral_Animation;
	int current_time;
	bool dispara;
public:
	LightShooterLateral(int x, int y);
	~LightShooterLateral(){}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif