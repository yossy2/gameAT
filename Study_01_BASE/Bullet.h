#pragma once
#include "Transform.h"

enum class TEAM
{
	PLAYER,
	ENEMY
};

class Bullet
{
private:
	Transform transform_;
	VECTOR vel_;

	TEAM team_;
	float aliveTime_;
	float speed_;
public:
	Bullet(int modelID,const VECTOR& pos,const Quaternion& rot,float speed,TEAM team);
	~Bullet();

	void Update();
	void Draw();
	void GetCapsule(VECTOR& start, VECTOR& end, float& radius);

	bool IsDeletable();
	void Hit();
	TEAM GetTeam();
};

