#pragma once
#include <vector>
#include "SceneBase.h"
#include <memory>

class SceneManager;
class SpaceDome;
class Stage;
class Player;
class DebriManager;
class Dangeon;
class BossShip;
class BulletManager;

class GameScene : public SceneBase
{

public:

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	SpaceDome* mSpaceDome;
	Stage* mStage;

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<DebriManager> mDebriManager;
	std::shared_ptr<BulletManager> mBulletManager;
	std::shared_ptr<Dangeon> dangeon_;
	std::shared_ptr<BossShip> bossShip_;
};
