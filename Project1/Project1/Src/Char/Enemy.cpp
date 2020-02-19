#include "Enemy.h"
#include "Bullet.h"
#include "../Engine/Graphics/DirectX.h"
#include "../Engine/Device.h"
#include <time.h>

Enemies enemies;
extern Bullet bullet;

void Enemies::InitEnemies()
{
	m_drawer2d.LoadTexture("Res/Enemy.png");

	srand((unsigned)time(NULL));

	CreateInterval = 1;

	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		enemies_info[i] =
		{
			WIN_W + 64,
			0.f,
			10.f,
			false,
			0,
			STATE::MOVE
		};
	}
}

void Enemies::UpdetaEnemies()
{
	CreateInterval--;

	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		// エネミー挙動
		if (enemies_info[i].IsAlive == true)
		{
			enemies_info[i].PosX -= enemies_info[i].MoveSpeed;
			
				// エネミーのAI
			if (enemies_info[i].State == STATE::WAIT)
			{
				Wait();
			}
			else if (enemies_info[i].State == STATE::MOVE)
			{
				Move();
			}
			else if (enemies_info[i].State == STATE::CHASE)
			{
				Chase();
			}
			else if (enemies_info[i].State == STATE::ATTACK)
			{
				Attack();
			}

			if (enemies_info[i].PosX <= -64.f || CheckHitBullet() == true)
			{
				enemies_info[i].IsAlive = false;
			}
		}

		// エネミー生成
		if (CreateInterval == 0)
		{
			CreateInterval = rand() % 30 + 10;

			if (enemies_info[i].IsAlive == false)
			{
				enemies_info[i].IsAlive = true;
				enemies_info[i].PosX = WIN_W + 64;
				enemies_info[i].PosY = rand() % (WIN_H - 40) + 40;
				enemies_info[i].EnemyType = rand() % 3;

				break;
			}
		}
	}
}

void Enemies::DrawEnemies()
{
	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		if (enemies_info[i].IsAlive == true)
		{
			t_VertexPos v{ Pos2(enemies_info[i].PosX, enemies_info[i].PosY), Pos2(enemies_info[i].EnemyType * 64.f, 0.f), Pos2((enemies_info[i].EnemyType + 1) * 64.f, 64.f) };
			m_drawer2d.DrawTexture(v, "Res/Enemy.png");
		}
	}
}

EnemiesInfo Enemies::GetEnemiesInfo(int num_)
{
	return enemies_info[num_];
}

void Enemies::Wait()
{

}

void Enemies::Move()
{

}

void Enemies::Chase()
{

}

void Enemies::Attack()
{

}

bool Enemies::CheckHitBullet()
{
	for (int i = 0; i < EnemiesMaxNum; i++)
	{
		for (int j = 0; j < BulletMaxNum; j++)
		{
			if (enemies_info[i].IsAlive == true && bullet.GetBulletInfo(j).IsMake == true &&
				enemies_info[i].PosX <= bullet.GetBulletInfo(j).PosX + 64.f &&
				enemies_info[i].PosX + 64.f >= bullet.GetBulletInfo(j).PosX &&
				enemies_info[i].PosY <= bullet.GetBulletInfo(j).PosY + 64.f &&
				enemies_info[i].PosY + 64.f >= bullet.GetBulletInfo(j).PosY)
			{
				bullet.DisappearBullet(j);
				return true;
			}
		}
	}

	return false;
}
