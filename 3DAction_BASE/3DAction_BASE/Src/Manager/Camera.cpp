#include <math.h>
#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/GravityManager.h"
#include "../Object/Common/Transform.h"
#include "../Object/Planet.h"
#include "Camera.h"
#include "../Common/TimeCount.h"

namespace
{
	constexpr float camera_rotate_speed = DX_PI_F;
}

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
	mGravityManager = manager->GetGravityManager();

	mAngles = VECTOR();
	mCameraUp = VECTOR();
	mMode = MODE::NONE;
	mPos = AsoUtility::VECTOR_ZERO;
	mTargetPos = AsoUtility::VECTOR_ZERO;
	mSyncTransform = nullptr;
}

Camera::~Camera()
{
}

void Camera::Init()
{

	ChangeMode(MODE::FIXED_POINT);

}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(10.0f, 30000.0f);

	switch (mMode)
	{
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	}

	// �J�����̐ݒ�
	SetCameraPositionAndTargetAndUpVec(
		mPos,
		mTargetPos,
		mCameraUp
	);

}

void Camera::SetBeforeDrawFixedPoint(void)
{
}

void Camera::SetBeforeDrawFollow(void)
{

	// �J��������
	ProcessRot();

	// �Ǐ]�ΏۂƂ̑��Έʒu�𓯊�
	SyncTransform();

}

void Camera::Draw()
{
}

void Camera::Release(void)
{
}

void Camera::ProcessRot(void)
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		mAngles.y += camera_rotate_speed * TimeCount::GetDeltaTime();
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		mAngles.y -= camera_rotate_speed * TimeCount::GetDeltaTime();
	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		mAngles.x = max(AsoUtility::Deg2RadF(-15.0f), mAngles.x - camera_rotate_speed * TimeCount::GetDeltaTime());
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		mAngles.x = min(AsoUtility::Deg2RadF(40.0f), mAngles.x + camera_rotate_speed * TimeCount::GetDeltaTime());
	}
}

void Camera::SetTransform(Transform* transform)
{
	mSyncTransform = transform;
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetAngles(void)
{
	return mAngles;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}

Quaternion Camera::GetQuaRot(void)
{
	return mQuaRot;
}

Quaternion Camera::GetQuaRotOutX(void)
{
	return mQuaRotOutX;
}

VECTOR Camera::GetDir(void)
{
	return VNorm(VSub(mTargetPos, mPos));
}

void Camera::ChangeMode(MODE mode)
{

	SetDefault();

	mMode = mode;
	switch (mMode)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FOLLOW:
		break;
	}

}

void Camera::SetDefault(void)
{

	// �J�����̏����ݒ�
	mPos = DEFAULT_CAMERA_POS;
	mTargetPos = AsoUtility::VECTOR_ZERO;

	mAngles.x = AsoUtility::Deg2RadF(30.0f);
	mAngles.y = 0.0f;
	mAngles.z = 0.0f;

	mQuaRot = Quaternion();

	mCameraUp = AsoUtility::DIR_U;

}

void Camera::SyncTransform(void)
{

	// ������̈ʒu
	VECTOR pos = mSyncTransform->pos;

	// �d�͂̕�������ɏ]��
	Quaternion gRot = mGravityManager->GetTransform()->quaRot;

	// ���ʂ���ݒ肳�ꂽY�����A��]������
	mQuaRotOutX = gRot.Mult(Quaternion::AngleAxis(mAngles.y, AsoUtility::AXIS_Y));

	// ���ʂ���ݒ肳�ꂽX�����A��]������
	mQuaRot = mQuaRotOutX.Mult(Quaternion::AngleAxis(mAngles.x, AsoUtility::AXIS_X));

	VECTOR localPos;

	// �����_(�ʏ�d�͂ł����Ƃ����Y�l��Ǐ]�ΏۂƓ����ɂ���)
	localPos = mQuaRotOutX.PosAxis(RELATIVE_TARGET_POS);
	mTargetPos = VAdd(pos, localPos);

	// �J�����ʒu
	localPos = mQuaRot.PosAxis(RELATIVE_CAMERA_POS_FOLLOW);
	mPos = VAdd(pos, localPos);

	// �J�����̏����
	mCameraUp = gRot.GetUp();

}
