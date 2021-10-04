#include "RollBall.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Unit.h"

namespace
{
    constexpr float init_height = 100.0f;
    constexpr float distance_to_owner = 100.0f;
    constexpr float radius = 10.0f;
}

RollBall::RollBall(SceneManager* manager, Unit* owner) :mSceneManager(manager),mOwner(owner)
{
}

RollBall::~RollBall()
{
}

void RollBall::Init()
{
	mPos = { 0.0,0.0,-distance_to_owner };

    VECTOR ownerPos = mOwner->GetPos();
    VectorSub(&mVecTargetToOwn, &mPos, &ownerPos);

    VECTOR u;
    VectorNormalize(&u, &mVecTargetToOwn);

    VectorScale(&mVecTargetToOwn, &u, distance_to_owner);

}

void RollBall::Update()
{
    RotateAroundTarget();
}

void RollBall::Draw()
{
    VECTOR ownerPos = mOwner->GetPos();
    VectorAdd(&mPos, &ownerPos, &mVecTargetToOwn);
    mPos.y = 100.0f;

    DrawSphere3D(mPos, radius, 32, 0xff0000, 0xff0000, true);

    VECTOR ownerForward = mOwner->GetForward();
    VECTOR normal;
    VectorNormalize(&normal, &mVecTargetToOwn);
    float cos = VDot(ownerForward, normal);
    float cross2D = ownerForward.x * normal.z - ownerForward.z * normal.x;
    cross2D /= abs(cross2D);

    DrawFormatString(0, 100, 0xfffffff, "Zƒ{[ƒ‹");
    DrawFormatString(0, 120, 0xfffffff, "Šp“x : %.1f",cross2D * AsoUtility::Rad2DegF(acos(cos)));
}

void RollBall::Release()
{
}

void RollBall::RotateAroundTarget()
{
    float rotate = 90.0f * mSceneManager->GetDeltaTime();
    rotate = AsoUtility::Deg2RadF(rotate);

    VECTOR in = mVecTargetToOwn;
    VectorRotationY(&mVecTargetToOwn, &in, rotate);
}
