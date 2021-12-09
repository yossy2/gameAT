#pragma once
#include "Transform.h"

class Turret
{
private:
	Transform mTransformBattery;
	Transform mTransformBarrel;
	Transform& mTransformParent;

	VECTOR mlocalPos;
	VECTOR mlocalRot;

	VECTOR mAngleAxis;

	float rotTime_ = 0.0f;

	float rot_speed_y = DX_PI_F / 6.0f;
	float rot_speed_x = DX_PI_F / 12.0f;

	bool isDead_ = false;
public:
	Turret(const VECTOR& pos, const VECTOR& rot,int battery,int burrel, Transform& transformParent);
	~Turret();

	void Update();
	void Draw();

	bool IsDead();
	bool CollCheck(const VECTOR& start, const VECTOR& end, float radius);

	Transform& GetTransform();
};

