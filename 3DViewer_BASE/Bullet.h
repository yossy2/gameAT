#pragma once
#include <DxLib.h>

class SceneManager;

class Bullet
{
private:
	VECTOR mPos;
	VECTOR mVel;
	bool mIsDeletable = false;
	float mAliveTime = 0;
	SceneManager* mSceneManager;

public:
	Bullet(VECTOR pos, VECTOR vel, SceneManager* manager);
	void Update();
	void Draw();
	bool IsDeletable()const;
};

