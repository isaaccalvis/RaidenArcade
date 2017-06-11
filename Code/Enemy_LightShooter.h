#ifndef __ENEMY_LightShooter_H__
#define __ENEMY_LightShooter_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_LightShooter : public Enemy {
private:
	Animation LightShooterAnim1;
	Animation LightShooterAnim2;
	Animation LightShooterAnim3;
	Animation LightShooterAnim4;
	Animation LightShooterAnim5;
	Animation LightShooterAnim6;
	Animation LightShooterAnim7;
	Animation LightShooterAnim8;
	Animation LightShooterAnim9;
	Animation LightShooterAnim10;
	Animation LightShooterAnim11;
	Animation LightShooterAnim12;
	Animation LightShooterAnim13;
	Animation LightShooterAnim14;
	Animation LightShooterAnim15;
	Animation LightShooterAnim16;

public:
	Enemy_LightShooter(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawUp();
	float rectaY;
	float rectaX;
};
#endif