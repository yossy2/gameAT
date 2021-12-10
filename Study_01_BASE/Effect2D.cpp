#include "Effect2D.h"
#include "TimeCount.h"
Effect2D::Effect2D(int image, float aliveTime, float size, const VECTOR& pos)
	:aliveTime_(aliveTime),size_(size),pos_(pos)
{
	image_.emplace_back(image);
}

void Effect2D::Update()
{
	animTime_ += TimeCount::GetDeltaTime();
	aliveTime_ -= TimeCount::GetDeltaTime();

	if (aliveTime_ <= 0) isDeletable_ = true;
}

void Effect2D::Draw()
{
	if (image_.size() == 1)
	{
		DrawBillboard3D(pos_, 0.5f, 0.5f, size_, 0.0f, image_[0], TRUE);
	}
	else
	{
		int x = static_cast<int>(aliveTime_ * 14.0f);
		DrawBillboard3D(pos_, 0.5f, 0.5f, size_, 0.0f, image_[x], TRUE);
	}
}

void Effect2D::SetImage(const std::vector<int>& image)
{
	image_ = image;
}

bool Effect2D::IsDeletable() const
{
	return isDeletable_;
}
