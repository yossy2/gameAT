#pragma once
#include "Transform.h"
#include <memory>
#include <list>

class Turret;
class Player;
class BulletManager;

class BossShip
{
private:
	Transform mTransform;
	std::list<std::shared_ptr<Turret>> turret_;
	BulletManager& bulletManager_;
	int battery_,barrel_;
	float attackInterval_ = 0;

public:
	BossShip(const VECTOR& pos,BulletManager& bulletManager);
	~BossShip();

	void EventUpdate();
	void Update();
	void Draw();

	bool CollisionCheck(std::shared_ptr<Player> player);
	Transform& GetTransform();

};

