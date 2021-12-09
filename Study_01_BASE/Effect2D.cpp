#include "Effect2D.h"
#include "TimeCount.h"
Effect2D::Effect2D(int image, float aliveTime, float size, const VECTOR& pos)
	:image_(image),aliveTime_(aliveTime),size_(size),pos_(pos)
{

}

void Effect2D::Update()
{
	aliveTime_ -= TimeCount::GetDeltaTime();

	if (aliveTime_ <= 0) isDeletable_ = true;
}

void Effect2D::Draw()
{
	DrawBillboard3D(pos_, 0.5f, 0.5f, size_, 0.0f, image_, TRUE);
}

bool Effect2D::IsDeletable() const
{
	return isDeletable_;
}
