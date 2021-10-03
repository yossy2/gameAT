#pragma once
#include <DxLib.h>

class SceneManager;

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

private:
	VECTOR mPos;
	VECTOR mAngles;

	void CheckMove();
	void CheckRotate();

	SceneManager* mSceneManager;
};

