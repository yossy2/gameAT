#include "Camera.h"
#include "AsoUtility.h"
#include "KeyCheck.h"
#include "SceneManager.h"

namespace
{
    float moveSpeed = 500.0f;
    float rotateSpeed = 90.0f;
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
    mPos = { 0.0f,200.0f,-500.0f };
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
    CheckRotate();
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

    SetCameraPositionAndAngle(mPos, mAngles.x, mAngles.y, mAngles.z);
}

VECTOR Camera::GetPosition() const
{
    return mPos;
}

VECTOR Camera::GetAngle() const
{
    return mAngles;
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
