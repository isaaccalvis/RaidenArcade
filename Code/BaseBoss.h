#ifndef __Base_Boss_H__
#define __Base_Boss_H__

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleEnemies.h"

class Base_Boss : public Enemy {
private:
	Animation Base_Boss_Animation;
	Animation Base_Boss_DestruccioAnimation;
	Animation Base_Boss_Dreta;
	Animation Base_Boss_Esquerra;
	Animation Base_Boss_Inicia;

	int current_time;
	bool dispara;
	int capsBoss[2];

	int estat;
public:
	Base_Boss(int x, int y);
	~Base_Boss() {}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif