#pragma once

#include "../Engine/Graphics/Drawer2D.h"

struct PlayerInfo
{
	float PosX;
	float PosY;
	float MoveSpeed;
	bool IsAttack;
	int AttackInterval;
	bool IsAlive;
};

class Player
{
public:
	void InitPlayer();
	void UpdatePlayer();
	void DrawPlayer();

	PlayerInfo GetPlayerInfo();

private:

	bool CheckHitEnemies();
	PlayerInfo player_info;

	Drawer2D m_drawer2d;

};