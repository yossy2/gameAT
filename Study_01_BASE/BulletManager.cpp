#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
	modelID_ = MV1LoadModel("Model/Shot/Shot.mv1");
}

BulletManager::~BulletManager()
{
	MV1DeleteModel(modelID_);
}

void BulletManager::Update()
{
	bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
		[](std::shared_ptr<Bullet> p) {return p->IsDeletable(); }), bullets_.end());

	for (auto b : bullets_)
	{
		b->Update();
	}
}

void BulletManager::Draw()
{
	for (auto b : bullets_)
	{
		b->Draw();
	}
}

void BulletManager::AddBullet(const VECTOR& pos, const Quaternion& rot, float speed, TEAM& team)
{
	bullets_.emplace_back(std::make_shared<Bullet>(modelID_,pos,rot,speed,team));
}

std::vector<std::shared_ptr<Bullet>>& BulletManager::GetBullets()
{
	return bullets_;
}
