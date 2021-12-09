#include "DebriManager.h"
#include <DxLib.h>
#include "SpaceDebri.h"
#include "RandomEngine.h"

namespace
{
	float size = 10000.0f;

	inline int GetKey(int x, int y, int z)
	{
		return ((x + 128) << 16) + ((y + 128) << 8) + (z + 128);
	}
}

void DebriManager::MakeDebriRandom(const DebriMapKey key, std::list<std::shared_ptr<SpaceDebri>>& list)
{
	Transform debriTransform;
	debriTransform.quaRotLocal = Quaternion();
	float scale = 50.0f;
	debriTransform.scl = { scale,scale,scale };
	for (int i = 0; i < 60; i++)
	{
		VECTOR pos = { static_cast<float>(key.x) * size,static_cast<float>(key.y) * size, static_cast<float>(key.z) * size };
		pos.x += RandomEngine::RandomFloat(0, size);
		pos.y += RandomEngine::RandomFloat(0, size);
		pos.z += RandomEngine::RandomFloat(0, size);

		debriTransform.pos = pos;
		debriTransform.quaRot = Quaternion::Euler(RandomEngine::RandomFloat(-DX_PI_F / 2.0f, DX_PI_F / 2.0f),
												  RandomEngine::RandomFloat(0, DX_PI_F * 2.0f), 
												  RandomEngine::RandomFloat(0, DX_PI_F * 2.0f));

		float scale = RandomEngine::RandomFloat(10.0f,30.0f);
		debriTransform.scl = { scale,scale,scale };

		list.emplace_back(std::make_shared<SpaceDebri>(baseModelID_[RandomEngine::RandomInt(0,4)], debriTransform));
	}
}

DebriMapKey DebriManager::ConvPlayerPos2Key(const VECTOR& pos)
{
	auto key = DebriMapKey((static_cast<int>(pos.x + 100000.0f) / size), (static_cast<int>(pos.y + 100000.0f) / size), (static_cast<int>(pos.z + 100000.0f) / size));
	return key.GetOffsetKey(-10, -10, -10);
}

DebriManager::DebriManager()
{
	baseModelID_[0] = MV1LoadModel("Model/Rock/Rock20.mv1");
	baseModelID_[1] = MV1LoadModel("Model/Rock/Rock21.mv1");
	baseModelID_[2] = MV1LoadModel("Model/Rock/Rock22.mv1");
	baseModelID_[3] = MV1LoadModel("Model/Rock/Rock23.mv1");
	baseModelID_[4] = MV1LoadModel("Model/Rock/Rock24.mv1");
}

DebriManager::~DebriManager()
{
	for (int i = 0; i < 5; i++)
	{
		MV1DeleteModel(baseModelID_[i]);
	}
}

void DebriManager::MakeDebri(const VECTOR& playerPos)
{
	DebriMapKey centerKey = ConvPlayerPos2Key(playerPos);

	if (oldPlayerKey == GetKey(centerKey.x, centerKey.y, centerKey.z)) return;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			for (int z = -1; z <= 1; z++)
			{
				int key = GetKey(centerKey.x + x, centerKey.y + y, centerKey.z + z);
				auto it = debriMap_.find(key);
				if (it != debriMap_.end()) continue;

				MakeDebriRandom(centerKey.GetOffsetKey(x, y, z),debriMap_[key]);
			}
		}
	}

	oldPlayerKey = GetKey(centerKey.x, centerKey.y, centerKey.z);
}

void DebriManager::Draw(const VECTOR& playerPos)
{
	DebriMapKey centerKey = ConvPlayerPos2Key(playerPos);

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			for (int z = -1; z <= 1; z++)
			{
				auto it = debriMap_.find(GetKey(centerKey.x + x,centerKey.y + y,centerKey.z + z));
				if (it == debriMap_.end()) continue;

				for (auto debri : (*it).second)
				{
					debri->Draw();
				}
			}
		}
	}
}
