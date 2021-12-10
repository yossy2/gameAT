#pragma once
#include "SceneBase.h"
#include <memory>

class SceneManager;
class SpaceDome;
class Player;
class DebriManager;
class BossShip;
class BulletManager;

class BattleScene :
    public SceneBase
{
public:

	BattleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	SpaceDome* mSpaceDome;

	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<DebriManager> mDebriManager;
	std::shared_ptr<BulletManager> mBulletManager;
	std::shared_ptr<BossShip> bossShip_;

	float restartCnt = 0;
};

