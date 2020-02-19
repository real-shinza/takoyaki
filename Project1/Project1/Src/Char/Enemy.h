#pragma once

#include "../Engine/Graphics/Drawer2D.h"

#define EnemiesMaxNum 15

enum STATE
{
	WAIT,
	MOVE,
	CHASE,
	ATTACK
};

struct EnemiesInfo
{
	float PosX;
	float PosY;
	float MoveSpeed;
	bool IsAlive;
	int EnemyType;
	STATE State;
};

class Enemies
{
public:
	void InitEnemies();
	void UpdetaEnemies();
	void DrawEnemies();

	EnemiesInfo GetEnemiesInfo(int num_);

private:
	void Wait();
	void Move();
	void Chase();
	void Attack();

	bool CheckHitBullet();

	int CreateInterval;

	EnemiesInfo enemies_info[EnemiesMaxNum];

	Drawer2D m_drawer2d;
};