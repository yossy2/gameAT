#include "Bullet.h"
#include "SceneManager.h"

Bullet::Bullet(VECTOR pos, VECTOR vel, SceneManager* manager):mPos(pos),mVel(vel),mSceneManager(manager)
{
}

void Bullet::Update()
{
    VECTOR move, newPos;
    VectorScale(&move, &mVel, mSceneManager->GetDeltaTime());
    VectorAdd(&newPos, &mPos, &move);
    mPos = newPos;

    mAliveTime += mSceneManager->GetDeltaTime();

    if (mAliveTime > 5.0f)
    {
        mIsDeletable = true;
    }
}

void Bullet::Draw()
{
    DrawSphere3D(mPos, 20.0f, 32, 0xff0000, 0xff0000, true);
}

bool Bullet::IsDeletable() const
{
    return mIsDeletable;
}
