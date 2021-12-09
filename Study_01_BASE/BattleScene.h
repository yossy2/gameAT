#pragma once
#include "SceneBase.h"
class BattleScene :
    public SceneBase
{
public:

	BattleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
};

