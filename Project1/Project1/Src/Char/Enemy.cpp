#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "../Engine/Graphics/DirectX.h"
#include "../Engine/Device.h"
#include <time.h>

Enemies enemies;
extern Bullet bullet;
extern Player player;

void Enemies::InitEnemies()
{
	m_drawer2d.LoadTexture("Res/Enemy.png");

	srand((unsigned)time(NULL));

	m_CreateInterval = 1;

	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		enemies_info[i] =
		{
			WIN_W + 64,
			0.f,
			5.f,
			false,
			0,
			rand() % 120 + 30,
			STATE::MOVE
		};
	}
}

void Enemies::UpdetaEnemies()
{
	m_CreateInterval--;

	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		// エネミー挙動
		if (enemies_info[i].m_IsAlive == true)
		{
			
			
				// エネミーのAI
			if (enemies_info[i].m_State == STATE::WAIT)
			{
				Wait(i);
			}
			else if (enemies_info[i].m_State == STATE::MOVE)
			{
				Move(i);
			}
			else if (enemies_info[i].m_State == STATE::CHASE)
			{
				Chase(i);
			}

			if (enemies_info[i].m_PosX <= -64.f || CheckHitBullet() == true)
			{
				enemies_info[i].m_IsAlive = false;
			}
		}

		// エネミー生成
		if (m_CreateInterval == 0)
		{
			m_CreateInterval = rand() % 60 + 10;

			if (enemies_info[i].m_IsAlive == false)
			{
				enemies_info[i].m_IsAlive = true;
				enemies_info[i].m_PosX = WIN_W + 64;
				enemies_info[i].m_PosY = rand() % (WIN_H - 40) + 40;
				enemies_info[i].m_EnemyType = rand() % 3;

				break;
			}
		}
	}
}

void Enemies::DrawEnemies()
{
	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		if (enemies_info[i].m_IsAlive == true)
		{
			t_VertexPos v{ Pos2(enemies_info[i].m_PosX, enemies_info[i].m_PosY), Pos2(enemies_info[i].m_EnemyType * 64.f, 0.f), Pos2((enemies_info[i].m_EnemyType + 1) * 64.f, 64.f) };
			m_drawer2d.DrawTexture(v, "Res/Enemy.png");
		}
	}
}

EnemiesInfo Enemies::GetEnemiesInfo(int num_)
{
	return enemies_info[num_];
}

void Enemies::Wait(int num_)
{
	enemies_info[num_].m_StateTimer--;

	if (enemies_info[num_].m_StateTimer == 0)
	{
		enemies_info[num_].m_StateTimer = rand() % 120 + 30;
		enemies_info[num_].m_State = STATE::MOVE;
	}

	if (GetDistance(num_) <= 250.f && player.GetPlayerInfo().IsAlive == true)
	{
		enemies_info[num_].m_State = STATE::CHASE;
	}
}

void Enemies::Move(int num_)
{
	enemies_info[num_].m_StateTimer--;
	enemies_info[num_].m_PosX -= enemies_info[num_].m_MoveSpeed;

	if (enemies_info[num_].m_StateTimer == 0)
	{
		enemies_info[num_].m_StateTimer = rand() % 120 + 30;
		enemies_info[num_].m_State = STATE::WAIT;
	}

	if (GetDistance(num_) <= 250.f && player.GetPlayerInfo().IsAlive == true)
	{
		enemies_info[num_].m_State = STATE::CHASE;
	}
}

void Enemies::Chase(int num_)
{
	float VecX = enemies_info[num_].m_PosX - player.GetPlayerInfo().PosX;
	float VecY = enemies_info[num_].m_PosY - player.GetPlayerInfo().PosY;

	float Length = sqrt(VecX * VecX + VecY * VecY);

	float NormalX = VecX / Length;
	float NormalY = VecY / Length;

	NormalX *= enemies_info[num_].m_MoveSpeed;
	NormalY *= enemies_info[num_].m_MoveSpeed;

	enemies_info[num_].m_PosX -= NormalX;
	enemies_info[num_].m_PosY -= NormalY;

	if (GetDistance(num_) >= 200.f || player.GetPlayerInfo().IsAlive == false)
	{
		enemies_info[num_].m_StateTimer = rand() % 120 + 30;
		enemies_info[num_].m_State = STATE::MOVE;
	}
}

bool Enemies::CheckHitBullet()
{
	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		for (int j = 0; j < BulletMaxNum; j++)
		{
			if (enemies_info[i].m_IsAlive == true && bullet.GetBulletInfo(j).IsMake == true &&
				enemies_info[i].m_PosX <= bullet.GetBulletInfo(j).PosX + 64.f &&
				enemies_info[i].m_PosX + 64.f >= bullet.GetBulletInfo(j).PosX &&
				enemies_info[i].m_PosY <= bullet.GetBulletInfo(j).PosY + 64.f &&
				enemies_info[i].m_PosY + 64.f >= bullet.GetBulletInfo(j).PosY)
			{
				bullet.DisappearBullet(j);
				return true;
			}
		}
	}

	return false;
}

float Enemies::GetDistance(int num_)
{
	float VecX = enemies_info[num_].m_PosX - player.GetPlayerInfo().PosX;
	float VecY = enemies_info[num_].m_PosY - player.GetPlayerInfo().PosY;

	float Length = sqrt(VecX * VecX + VecY * VecY);

	return Length;
}