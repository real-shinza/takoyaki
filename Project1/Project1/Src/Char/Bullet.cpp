#include "Bullet.h"
#include "Player.h"
#include "../Engine/Graphics/DirectX.h"
#include "../Engine/Device.h"

Bullet bullet;
extern Player player;

void Bullet::InitBullet()
{
	m_drawer2d.LoadTexture("Res/PlayerBullet.png");

	for (int i = 0; i < BulletMaxNum; i++)
	{
		bullet_info[i] =
		{
			0.f,
			0.f,
			15.f,
			false
		};
	}
}

void Bullet::UpdetaBullet()
{
	for (int i = 0; i < BulletMaxNum; i++)
	{
		if (bullet_info[i].IsMake == true)
		{
			bullet_info[i].PosX += bullet_info[i].MoveSpeed;
			if (bullet_info[i].PosX >= WIN_W + 64.f)
			{
				bullet_info[i].IsMake = false;
			}
		}
	}
}

void Bullet::DrawBullet()
{
	for (int i = 0; i < BulletMaxNum; i++)
	{
		if (bullet_info[i].IsMake == true)
		{
			t_VertexPos v{ Pos2(bullet_info[i].PosX, bullet_info[i].PosY), Pos2(0.f, 0.f), Pos2(64.f, 64.f) };
			m_drawer2d.DrawTexture(v, "Res/PlayerBullet.png");
		}
	}
}

void Bullet::CreateBullet()
{
	for (int i = 0; i < BulletMaxNum; i++)
	{
		if (bullet_info[i].IsMake == false)
		{
			bullet_info[i].PosX = player.GetPlayerInfo().PosX + 64.f;
			bullet_info[i].PosY = player.GetPlayerInfo().PosY;
			bullet_info[i].IsMake = true;

			break;
		}
	}
}

void Bullet::DisappearBullet(int num_)
{
	bullet_info[num_].IsMake = false;
}

BulletInfo Bullet::GetBulletInfo(int num_)
{
	return bullet_info[num_];
}
