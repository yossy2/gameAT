#pragma once
#include <vector>
#include "SceneBase.h"
class SceneManager;
class SpaceDome;
class Stage;

class GameScene : public SceneBase
{

public:

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	SpaceDome* mSpaceDome;
	Stage* mStage;


};
