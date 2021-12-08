#pragma once
#include "Transform.h"

class SceneManager;

class Player
{
private:
	Transform mTransform;

	SceneManager* mSceneManager;

	void Rotate();
public:
	Player(SceneManager* sceneManager);
	~Player();
	void Update();
	void Draw();

	const Transform& GetTransform()const;
};

