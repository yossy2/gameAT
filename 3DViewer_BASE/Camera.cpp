#include "Camera.h"
#include "AsoUtility.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Unit.h"

namespace
{
    float moveSpeed = 500.0f;
    float rotateSpeed = 90.0f;

    constexpr float height = 200.0f;
    constexpr float distance_to_target = 500.0f;
}

namespace
{
    VECTOR RotateVector(VECTOR vec, VECTOR angle)
    {
        VECTOR ret;
        MATRIX mat = MMult(MMult(MGetRotX(angle.x),MGetRotY(angle.y)),MGetRotZ(angle.z));
        VectorTransform(&ret, &vec, &mat);
        return ret;
    }
}

Camera::Camera(SceneManager* manager):mSceneManager(manager)
{
    mPos = { 0.0f,height,-distance_to_target };
    mAngles = { AsoUtility::Deg2RadF(30.0f),0.0f,0.0f };
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
    //CheckMove();
    //CheckRotate();

    RotateAroundTarget();
}

void Camera::Draw()
{
}

void Camera::Release()
{
}

void Camera::SetBeforeDraw()
{
    //SetCameraNearFar(0.0f, 1500.0f);

    //SetCameraPositionAndAngle(mPos, mAngles.x, mAngles.y, mAngles.z);

    VECTOR targetPos = mTarget->GetPos();
    VectorAdd(&mPos, &targetPos, &mTargetToCamera);
    SetCameraPositionAndTargetAndUpVec(mPos, mTarget->GetPos(), { 0,1.0f,0 });
}

VECTOR Camera::GetPosition() const
{
    return mPos;
}

VECTOR Camera::GetAngle() const
{
    return mAngles;
}

VECTOR Camera::GetVecTargetToCamera() const
{
    return mTargetToCamera;
}

void Camera::SetTarget(Unit* unit)
{
    mTarget = unit;
    VECTOR targetPos = mTarget->GetPos();
    VectorSub(&mTargetToCamera, &mPos ,&targetPos);

    VECTOR u;
    VectorNormalize(&u, &mTargetToCamera);

    VectorScale(&mTargetToCamera, &u, distance_to_target);
}

void Camera::CheckMove()
{
    float move = moveSpeed * mSceneManager->GetDeltaTime();

    // ‘O•û
    if (keyNew[KEY_P2_UP])
    {
        VECTOR vec,rotate,add;
        rotate = RotateVector({ 0.0,0.0,1.0f }, mAngles);
        VectorScale(&vec,&rotate,move);
        VectorAdd(&add, &mPos, &vec);
        mPos = add;
    }

    if (keyNew[KEY_P2_DOWN])
    {
        VECTOR vec, rotate, add;
        rotate = RotateVector({ 0.0,0.0,-1.0f }, mAngles);
        VectorScale(&vec, &rotate, move);
        VectorAdd(&add, &mPos, &vec);
        mPos = add;
    }

    if (keyNew[KEY_P2_RIGHT])
    {
        VECTOR vec, rotate, add;
        rotate = RotateVector({ 1.0f,0.0,0.0f }, mAngles);
        VectorScale(&vec, &rotate, move);
        VectorAdd(&add, &mPos, &vec);
        mPos = add;
    }

    if (keyNew[KEY_P2_LEFT])
    {
        VECTOR vec, rotate, add;
        rotate = RotateVector({ -1.0f,0.0,0.0f }, mAngles);
        VectorScale(&vec, &rotate, move);
        VectorAdd(&add, &mPos, &vec);
        mPos = add;
    }

    if (keyNew[KEY_P2_B])
    {
        VECTOR vec, rotate, add;
        rotate = RotateVector({ 0.0,1.0f,0.0f }, mAngles);
        VectorScale(&vec, &rotate, move);
        VectorAdd(&add, &mPos, &vec);
        mPos = add;
    }

    if (keyNew[KEY_P2_A])
    {
        VECTOR vec, rotate, add;
        rotate = RotateVector({ 0.0,-1.0f,0.0f }, mAngles);
        VectorScale(&vec, &rotate, move);
        VectorAdd(&add, &mPos, &vec);
        mPos = add;
    }
}

void Camera::CheckRotate()
{
    float rotate = rotateSpeed * mSceneManager->GetDeltaTime();
    rotate = AsoUtility::Deg2RadF(rotate);

    if (keyNew[KEY_P1_UP])
    {
        mAngles.x += rotate;
    }

    if (keyNew[KEY_P1_DOWN])
    {
        mAngles.x -= rotate;
    }

    if (keyNew[KEY_P1_RIGHT])
    {
        mAngles.y += rotate;
    }

    if (keyNew[KEY_P1_LEFT])
    {
        mAngles.y -= rotate;
    }

    if (keyNew[KEY_P1_A])
    {
        mAngles.z += rotate;
    }

    if (keyNew[KEY_P1_B])
    {
        mAngles.z -= rotate;
    }
}

void Camera::RotateAroundTarget()
{
    float rotate = rotateSpeed * mSceneManager->GetDeltaTime();
    rotate = AsoUtility::Deg2RadF(rotate);

    if(CheckHitKey(KEY_INPUT_RIGHT))
    {
        VECTOR in = mTargetToCamera;
        VectorRotationY(&mTargetToCamera, &in, rotate);
    }

    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        VECTOR in = mTargetToCamera;
        VectorRotationY(&mTargetToCamera, &in, -rotate);
    }

}
