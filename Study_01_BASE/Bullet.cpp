#include "Bullet.h"
#include "TimeCount.h"

Bullet::Bullet(int modelID, const VECTOR& pos, const Quaternion& rot,float speed, TEAM team):speed_(speed),team_(team)
{
	aliveTime_ = 10.0f;
	transform_.modelId = MV1DuplicateModel(modelID);
	transform_.pos = pos;
	transform_.scl = VGet(1.0f, 1.0f, 1.0f);
	transform_.quaRot = rot;
	transform_.quaRotLocal = Quaternion::Euler(DX_PI_F / 2.0f, 0.0f, 0.0f);;
	transform_.Update();
}

Bullet::~Bullet()
{
	MV1DeleteModel(transform_.modelId);
}

void Bullet::Update()
{
	transform_.pos = VAdd(transform_.pos, VScale(transform_.GetForward(), speed_ * TimeCount::GetDeltaTime()));
	transform_.Update();

	aliveTime_ -= TimeCount::GetDeltaTime();
}

void Bullet::Draw()
{
	MV1DrawModel(transform_.modelId);
	/*auto pos = VAdd(transform_.pos, VScale(transform_.GetBack(), 50.0f));
	DrawCapsule3D(pos, VAdd(pos, VScale(transform_.GetForward(), 100.0f)), 50.0f, 8,0xffffff, 0xffffff, false);*/
}

void Bullet::GetCapsule(VECTOR& start, VECTOR& end, float& radius)
{
	start = VAdd(transform_.pos, VScale(transform_.GetBack(), 50.0f));
	end = VAdd(start, VScale(transform_.GetForward(), 100.0f));
	radius = 50.0f;
}

bool Bullet::IsDeletable()
{
	return aliveTime_ <= 0;
}

void Bullet::Hit()
{
	aliveTime_ = 0;
}

TEAM Bullet::GetTeam()
{
	return team_;
}
