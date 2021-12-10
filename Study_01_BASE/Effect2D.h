#pragma once
#include <DxLib.h>
#include <vector>

class Effect2D
{
private:
	std::vector<int> image_;
	float aliveTime_;
	float size_;
	float animTime_;
	VECTOR pos_;

	bool isDeletable_ = false;
public:
	Effect2D(int image, float aliveTime, float size, const VECTOR& pos);
	void Update();
	void Draw();

	void SetImage(const std::vector<int>& image);
	bool IsDeletable()const;
};

