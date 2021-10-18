#pragma once
#include "Transform.h"

class SceneManager;

class SpaceDome
{
public:

	SpaceDome(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	SceneManager* mSceneManager;

	// ���f������̊�{���
	Transform mTransform;
};

