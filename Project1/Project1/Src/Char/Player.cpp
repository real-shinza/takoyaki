#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "../Engine/Graphics/DirectX.h"
#include "../Engine/Device.h"

#define PlayerAttackInterval 30

Player player;
extern Bullet bullet;
extern Enemies enemies;

void Player::InitPlayer()
{
	m_drawer2d.LoadTexture("Res/Player.png");

	player_info =
	{
		100.f,
		WIN_H / 2,
		10.f,
		false,
		PlayerAttackInterval,
		true
	};
}

void Player::UpdatePlayer()
{
	if (CheckHitEnemies())
	{
		player_info.IsAlive = false;
	}

	if (player_info.IsAlive == true)
	{
		if (Device::KeyOn(VK_UP) && player_info.PosY >= 64.f)
		{
			player_info.PosY -= player_info.MoveSpeed;
		}

		if (Device::KeyOn(VK_DOWN) && player_info.PosY <= WIN_H - 64.f)
		{
			player_info.PosY += player_info.MoveSpeed;
		}

		if (Device::KeyPress(VK_SPACE))
		{
			bullet.CreateBullet();
		}
	}
}

void Player::DrawPlayer()
{
	if (player_info.IsAlive == true)
	{
		t_VertexPos v{ Pos2(player_info.PosX, player_info.PosY), Pos2(0.f, 0.f), Pos2(256.f, 128.f) };
			m_drawer2d.DrawTexture(v, "Res/Player.png");
	}
}

PlayerInfo Player::GetPlayerInfo()
{
	return player_info;
}

bool Player::CheckHitEnemies()
{
	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		if (player_info.IsAlive == true && enemies.GetEnemiesInfo(i).IsAlive == true &&
			player_info.PosX <= enemies.GetEnemiesInfo(i).PosX + 64.f &&
			player_info.PosX + 256.f >= enemies.GetEnemiesInfo(i).PosX &&
			player_info.PosY <= enemies.GetEnemiesInfo(i).PosY + 64.f &&
			player_info.PosY + 128.f >= enemies.GetEnemiesInfo(i).PosY)
		{
			return true;
		}
	}
	return false;
}
