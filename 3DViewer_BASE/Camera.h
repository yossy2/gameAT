#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class Camera
{
public:
	Camera(SceneManager* manager);
	~Camera();

	void Init();
	void Update();
	void Draw();
	void Release();

	void SetBeforeDraw();

	VECTOR GetPosition()const;
	VECTOR GetAngle()const;
	VECTOR GetVecTargetToCamera()const;

	void SetTarget(Unit* unit);

private:
	VECTOR mPos;
	VECTOR mAngles;
	VECTOR mTargetToCamera;

	void CheckMove();
	void CheckRotate();

	void RotateAroundTarget();

	SceneManager* mSceneManager;
	Unit* mTarget;
};

