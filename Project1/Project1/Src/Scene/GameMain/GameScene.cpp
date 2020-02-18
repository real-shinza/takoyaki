#include "GameScene.h"
#include "../../Char/Player.h"
#include "../../Char/Bullet.h"
#include "../../Char/Enemy.h"

extern Player player;
extern Bullet bullet;
extern Enemies enemies;

GameScene::~GameScene()
{
}


void GameScene::Init()
{
	player.InitPlayer();
	bullet.InitBullet();
	enemies.InitEnemies();
	// シーン遷移
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {

	player.UpdatePlayer();
	bullet.UpdetaBullet();
	enemies.UpdetaEnemies();

	if (Device::KeyPress('A')) { m_state = SceneState::END; }
}

SceneID GameScene::End() {
	m_state = SceneState::INIT;


	return SceneID::RESULT;
}

SceneID GameScene::Control() {
	switch (m_state)
	{
	case SceneState::INIT:
		Init();
		break;
	case SceneState::UPDATE:
		Update();
		break;
	case SceneState::END:
		return End();
	}
	return SceneID::GAME;
}

void GameScene::Draw() {
	player.DrawPlayer();
	bullet.DrawBullet();
	enemies.DrawEnemies();

	t_Vec2 font_pos(0.f, 0.f);
	m_drawer2d.DrawFont(font_pos, "ゲームシーンを表示");

}

