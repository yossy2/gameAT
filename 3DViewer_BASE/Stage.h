#pragma once
#include <DxLib.h>

class SceneManager;

class Stage
{
public:
	Stage(SceneManager* manager);
	void Init();
	void Update();
	void Draw();
	void Release();

private:
	SceneManager* mSceneManager;
	int mModelID;
	VECTOR mModelPos;
};

