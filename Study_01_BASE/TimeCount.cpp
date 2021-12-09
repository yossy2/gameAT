#include "TimeCount.h"
#include <DxLib.h>

TimeCount::TimeCount() :nowCount_(0),deltaTime_(0)
{
	
}

int TimeCount::GetCount_()
{
	return nowCount_;
}

float TimeCount::GetDeltaTime_()
{
	return deltaTime_;
}

void TimeCount::Update_()
{
	auto count = GetNowCount();
	auto milli = count - nowCount_;

	// ƒ~ƒŠ•b‚©‚ç•b‚É•ÏŠ·
	deltaTime_ = static_cast<float>(milli) / 1000.0f;
	if (deltaTime_ > 1.0) deltaTime_ = 0;
	nowCount_ = count;
}

TimeCount& TimeCount::Instance()
{
	static TimeCount instance;
	return instance;
}

int TimeCount::GetCount()
{
	return Instance().GetCount_();
}

float TimeCount::GetDeltaTime()
{
	return Instance().GetDeltaTime_();
}

void TimeCount::Update()
{
	Instance().Update_();
}

TimeCount::~TimeCount()
{
}
