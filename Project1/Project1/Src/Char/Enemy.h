#pragma once

#include "../Engine/Graphics/Drawer2D.h"

#define EnemiesMaxNum 5

enum STATE
{
	WAIT,
	MOVE,
	CHASE,
};

struct EnemiesInfo
{
	float m_PosX;
	float m_PosY;
	float m_MoveSpeed;
	bool m_IsAlive;
	int m_EnemyType;
	int m_StateTimer;
	STATE m_State;
};

class Enemies
{
public:
	void InitEnemies();
	void UpdetaEnemies();
	void DrawEnemies();

	EnemiesInfo GetEnemiesInfo(int num_);

private:
	void Wait(int num_);
	void Move(int num_);
	void Chase(int num_);

	bool CheckHitBullet();
	float GetDistance(int num_);

	int m_CreateInterval;

	EnemiesInfo enemies_info[EnemiesMaxNum];

	Drawer2D m_drawer2d;
};