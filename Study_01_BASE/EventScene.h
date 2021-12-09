#pragma once
#include "SceneBase.h"
#include <memory>

class SpaceDome;
class BossShip;
class BulletManager;

class EventScene :
    public SceneBase
{
public:

	EventScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	float cnt_ = 0;

	SpaceDome* mSpaceDome;
	std::shared_ptr<BossShip> bossShip_;
	std::shared_ptr<BulletManager> mBulletManager;

};

