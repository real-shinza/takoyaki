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
		7.f,
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
		PlayerControl();

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
		t_VertexPos v{ Pos2(player_info.PosX, player_info.PosY), Pos2(0.f, 0.f), Pos2(64.f, 64.f) };
			m_drawer2d.DrawTexture(v, "Res/Player.png");
	}
}

PlayerInfo Player::GetPlayerInfo()
{
	return player_info;
}

void Player::PlayerControl()
{
	float VecUp = 0.f;
	float VecDown = 0.f;
	float VecRight = 0.f;
	float VecLeft = 0.f;

	if (Device::KeyOn(VK_UP) && player_info.PosY >= 64.f)
	{
		VecUp = -player_info.MoveSpeed;
	}

	if (Device::KeyOn(VK_DOWN) && player_info.PosY <= WIN_H - 64.f)
	{
		VecDown = player_info.MoveSpeed;
	}

	if (Device::KeyOn(VK_LEFT) && player_info.PosX >= 64.f)
	{
		VecRight = -player_info.MoveSpeed;
	}

	if (Device::KeyOn(VK_RIGHT) && player_info.PosX <= WIN_W - 64.f)
	{
		VecLeft = player_info.MoveSpeed;
	}

	float VecX = VecLeft + VecRight;
	float VecY = VecUp + VecDown;

	if (VecX != 0.f || VecY != 0.f)
	{
		float Length = sqrt(VecX * VecX + VecY * VecY);

		float NormalX = VecX / Length;
		float NormalY = VecY / Length;

		NormalX *= player_info.MoveSpeed;
		NormalY *= player_info.MoveSpeed;

		player_info.PosX += NormalX;
		player_info.PosY += NormalY;
	}
}

bool Player::CheckHitEnemies()
{
	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		if (player_info.IsAlive == true && enemies.GetEnemiesInfo(i).m_IsAlive == true &&
			player_info.PosX <= enemies.GetEnemiesInfo(i).m_PosX + 64.f &&
			player_info.PosX + 64.f >= enemies.GetEnemiesInfo(i).m_PosX &&
			player_info.PosY <= enemies.GetEnemiesInfo(i).m_PosY + 64.f &&
			player_info.PosY + 64.f >= enemies.GetEnemiesInfo(i).m_PosY)
		{
			return true;
		}
	}
	return false;
}
