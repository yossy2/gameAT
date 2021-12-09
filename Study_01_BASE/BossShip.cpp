#include "BossShip.h"
#include "TimeCount.h"
#include "Turret.h"
#include "AsoUtility.h"
#include "Player.h"
#include "BulletManager.h"
#include "Bullet.h"

namespace
{
	constexpr float move_speed = 300.0f;
}

BossShip::BossShip(const VECTOR& pos, BulletManager& bulletManager):bulletManager_(bulletManager)
{
	mTransform.SetModel(MV1LoadModel("Model/BossShip/BossShip.mv1"));

	float scale = 2.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0, 0.0f, 0.0f);
	mTransform.quaRotLocal = Quaternion::Euler(0, DX_PI_F, 0.0f);
	mTransform.pos = pos;

	mTransform.Update();
	MV1SetupCollInfo(mTransform.modelId, -1, 8, 8, 8);

	battery_ = MV1LoadModel("Model/BossShip/Turret.mv1");
	barrel_ = MV1LoadModel("Model/BossShip/Turret_Gun.mv1");

	auto turret = std::make_shared<Turret>(VGet(4.5f, 5.5f, 7.8f), VGet(0, 0, AsoUtility::Deg2RadF(-18.0f)), battery_, barrel_, mTransform);
	turret_.emplace_back(turret);

	turret = std::make_shared<Turret>(VGet(-4.5f, 5.5f, 7.8f), VGet(0, 0, AsoUtility::Deg2RadF(18.0f)), battery_, barrel_, mTransform);
	turret_.emplace_back(turret);

	turret = std::make_shared<Turret>(VGet(4.5f, 5.5f, 0.0f), VGet(AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(90.0f), 0), battery_, barrel_, mTransform);
	turret_.emplace_back(turret);

	turret = std::make_shared<Turret>(VGet(-4.5f, 5.5f, 0.0f), VGet(AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(-90.0f), 0), battery_, barrel_, mTransform);
	turret_.emplace_back(turret);

	turret = std::make_shared<Turret>(VGet(3.5f, 5.0f, -17.8f), VGet(0, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(18.0f)), battery_, barrel_, mTransform);
	turret_.emplace_back(turret);

	turret = std::make_shared<Turret>(VGet(-3.5f, 5.0f, -17.8f), VGet(0, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(-18.0f)), battery_, barrel_, mTransform);
	turret_.emplace_back(turret);
}

BossShip::~BossShip()
{
	MV1DeleteModel(mTransform.modelId);
	MV1DeleteModel(barrel_);
	MV1DeleteModel(battery_);
}

void BossShip::EventUpdate()
{
	mTransform.pos = VAdd(mTransform.pos, VScale(mTransform.GetForward(), move_speed * TimeCount::GetDeltaTime()));
	mTransform.Update();

	for (auto t : turret_)
	{
		t->Update();
	}

	attackInterval_ -= TimeCount::GetDeltaTime();

	if (attackInterval_ <= 0)
	{
		TEAM team = TEAM::ENEMY;

		for (auto t : turret_)
		{
			auto& transform = t->GetTransform();
			bulletManager_.AddBullet(transform.pos, transform.quaRot, 2500.0f, team);

		}
		attackInterval_ = 2.0f;
	}
}

void BossShip::Update()
{
	mTransform.pos = VAdd(mTransform.pos, VScale(mTransform.GetForward(), move_speed * TimeCount::GetDeltaTime()));
	auto axisY = Quaternion::AngleAxis(0.001f, AsoUtility::AXIS_Y);
	mTransform.quaRot = mTransform.quaRot.Mult(axisY);
	mTransform.Update();

	for (auto t : turret_)
	{
		t->Update();
	}

	MV1RefreshCollInfo(mTransform.modelId);

	auto& bullets = bulletManager_.GetBullets();

	for (auto b : bullets)
	{
		if (b->GetTeam() == TEAM::ENEMY) continue;

		VECTOR start, end;
		float radius;

		b->GetCapsule(start, end, radius);

		for (auto t : turret_)
		{
			if (t->IsDead()) continue;
			if (t->CollCheck(start, end, radius))
			{
				b->Hit();
				break;
			}
		}
	}

	attackInterval_ -= TimeCount::GetDeltaTime();

	if (attackInterval_ <= 0)
	{
		TEAM team = TEAM::ENEMY;

		for (auto t : turret_)
		{
			auto& transform = t->GetTransform();
			bulletManager_.AddBullet(transform.pos, transform.quaRot, 2500.0f, team);

		}
		attackInterval_ = 2.0f;
	}
}

void BossShip::Draw()
{
	MV1DrawModel(mTransform.modelId);
	for (auto t : turret_)
	{
		t->Draw();
	}
}

bool BossShip::CollisionCheck(std::shared_ptr<Player> player)
{
	VECTOR start, end;
	float radius;

	player->GetCapsule(start, end, radius);
	auto hit = MV1CollCheck_Capsule(mTransform.modelId, -1, start, end, radius);

	if (hit.HitNum == 0)
	{
		MV1CollResultPolyDimTerminate(hit);
		return false;
	}
	MV1CollResultPolyDimTerminate(hit);
	return true;
}

Transform& BossShip::GetTransform()
{
	return mTransform;
}
