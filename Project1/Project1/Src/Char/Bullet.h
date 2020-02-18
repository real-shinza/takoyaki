#pragma once

#include "../Engine/Graphics/Drawer2D.h"

#define BulletMaxNum 15

struct BulletInfo
{
	float PosX;
	float PosY;
	float MoveSpeed;
	bool IsMake;
};

class Bullet
{
public:
	void InitBullet();
	void UpdetaBullet();
	void DrawBullet();

	void CreateBullet();
	void DisappearBullet(int num_);

	BulletInfo GetBulletInfo(int num_);

private:
	BulletInfo bullet_info[BulletMaxNum];

	Drawer2D m_drawer2d;

};