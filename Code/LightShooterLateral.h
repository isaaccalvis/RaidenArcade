#ifndef __LightShooterLateral_H__
#define __LightShooterLateral_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class LightShooterLateral : public Enemy {
private:
	Animation LightShooterLateral_Animation1;
	Animation LightShooterLateral_Animation2;
	Animation LightShooterLateral_Animation3;
	Animation LightShooterLateral_Animation4;
	Animation LightShooterLateral_Animation5;
	Animation LightShooterLateral_Animation6;
	Animation LightShooterLateral_Animation7;
	Animation LightShooterLateral_Animation8;
	Animation LightShooterLateral_Animation9;
	Animation LightShooterLateral_Animation10;
	Animation LightShooterLateral_Animation11;
	Animation LightShooterLateral_Animation12;
	Animation LightShooterLateral_Animation13;
	Animation LightShooterLateral_Animation14;
	Animation LightShooterLateral_Animation15;
	Animation LightShooterLateral_Animation16;

	int current_time;
	bool dispara;
	int state;
public:
	LightShooterLateral(int x, int y);
	~LightShooterLateral() {}
	void Move();
	void OnCollision(Collider* collider);
	void DrawUp();
	float rectaY;
	float rectaX;
};
#endif