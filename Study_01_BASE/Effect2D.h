#pragma once
#include <DxLib.h>

class Effect2D
{
private:
	int image_;
	float aliveTime_;
	float size_;
	VECTOR pos_;

	bool isDeletable_ = false;
public:
	Effect2D(int image, float aliveTime, float size, const VECTOR& pos);
	void Update();
	void Draw();

	bool IsDeletable()const;
};

