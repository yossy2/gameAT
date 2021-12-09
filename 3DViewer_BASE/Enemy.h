#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class Enemy
{
public:
	Enemy(SceneManager* manager,Unit* unit);
	void Init();
	void Update();
	void Draw();
	void Release();

	VECTOR GetPos()const;
	VECTOR GetForward()const;

private:
	SceneManager* mSceneManager;
	Unit* mUnit;

	int mModelID;

	VECTOR mPos;
	VECTOR mAngles;


	float mRange;
	float mAngle;
};

