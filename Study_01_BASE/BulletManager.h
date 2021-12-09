#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
class Bullet;
enum class TEAM;

class BulletManager
{
private:
	std::vector<std::shared_ptr<Bullet>> bullets_;
	int modelID_;
public:
	BulletManager();
	~BulletManager();
	void Update();
	void Draw();
	void AddBullet(const VECTOR& pos, const Quaternion& rot,float speed,TEAM& team);

	std::vector<std::shared_ptr<Bullet>>& GetBullets();
};

