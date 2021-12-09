#include "Turret.h"
#include "AsoUtility.h"
#include "TimeCount.h"

namespace
{
	constexpr float rot_speed_y = DX_PI_F / 6.0f;
	constexpr float rot_speed_x = DX_PI_F / 12.0f;
}

Turret::Turret(const VECTOR& pos,const VECTOR& rot, int battery, int burrel, Transform& transformParent)
	:mlocalPos(pos),mlocalRot(rot),mTransformParent(transformParent)
{
	mTransformBattery.SetModel(MV1DuplicateModel(battery));
	mTransformBarrel.SetModel(MV1DuplicateModel(burrel));

	float scale = 80.0f;
	mTransformBattery.scl = { scale,scale,scale };
	mTransformBarrel.scl = { scale,scale,scale };
	mTransformBattery.quaRotLocal = Quaternion::Euler(0.0f, DX_PI_F, 0.0f);
	mTransformBarrel.quaRotLocal = Quaternion::Euler(0.0f, DX_PI_F, 0.0f);
	mTransformBattery.pos = VGet(0,0,0);

	// �^���b�g�̉�]���{�X(�e)�̉�]�Ɠ����ɂ���
	mTransformBattery.quaRot = mTransformParent.quaRot;
	// �擾���Ă�����]���g���āA��]�ɉ��������΍��W���擾����
	auto localPos = Quaternion::PosAxis(mTransformBattery.quaRot, mlocalPos);
	// �e�̍��W�Ɍv�Z�������΍��W��������
	mTransformBattery.pos = VAdd(mTransformParent.pos, VScale(localPos, 80.0f));

	// ��]����������]�ʂ��v�Z���Ă���
	Quaternion localRot;
	// �܂��͐e����̑��Ή�]
	auto axis = Quaternion::AngleAxis(mlocalRot.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);
	axis = Quaternion::AngleAxis(mlocalRot.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);
	axis = Quaternion::AngleAxis(mlocalRot.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	mAngleAxis = VGet(-DX_PI_F / 18.0f, -DX_PI_F / 6.0f, 0);

	// ���ɍ���̃t���[���ŉ�]����������]��(�C�䂾��Y���A�C�g����X��)
	auto axisY = Quaternion::AngleAxis(mAngleAxis.y, AsoUtility::AXIS_Y);
	auto localRotY = localRot.Mult(axisY);

	// �e�̉�]���q�̉�]�ɑ������Ă���O��ŁA����v�Z������]��������
	mTransformBattery.quaRot = mTransformBattery.quaRot.Mult(localRotY);
	mTransformBattery.Update();

	Quaternion localRot2;
	auto axisX = Quaternion::AngleAxis(mAngleAxis.x, AsoUtility::AXIS_X);
	auto localRotX = localRot2.Mult(axisX);
	mTransformBarrel.pos = mTransformBattery.pos;
	mTransformBarrel.quaRot = mTransformBattery.quaRot;
	mTransformBarrel.quaRot = mTransformBarrel.quaRot.Mult(localRotX);
	mTransformBarrel.Update();
}

Turret::~Turret()
{
	MV1DeleteModel(mTransformBarrel.modelId);
	MV1DeleteModel(mTransformBattery.modelId);
}

void Turret::Update()
{
	if (isDead_) return;

	mAngleAxis.y += rot_speed_y * TimeCount::GetDeltaTime();
	mAngleAxis.x += rot_speed_x * TimeCount::GetDeltaTime();

	rotTime_ += TimeCount::GetDeltaTime();

	if (rotTime_ >= 2.0f)
	{
		rotTime_ = 0;
		rot_speed_x *= -1.0f;
		rot_speed_y *= -1.0f;
	}

	// �^���b�g�̉�]���{�X(�e)�̉�]�Ɠ����ɂ���
	mTransformBattery.quaRot = mTransformParent.quaRot;
	// �擾���Ă�����]���g���āA��]�ɉ��������΍��W���擾����
	auto localPos = Quaternion::PosAxis(mTransformBattery.quaRot, mlocalPos);
	// �e�̍��W�Ɍv�Z�������΍��W��������
	mTransformBattery.pos = VAdd(mTransformParent.pos, VScale(localPos, 80.0f));

	// ��]����������]�ʂ��v�Z���Ă���
	Quaternion localRot;
	// �܂��͐e����̑��Ή�]
	auto axis = Quaternion::AngleAxis(mlocalRot.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);
	axis = Quaternion::AngleAxis(mlocalRot.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);
	axis = Quaternion::AngleAxis(mlocalRot.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	// ���ɍ���̃t���[���ŉ�]����������]��(�C�䂾��Y���A�C�g����X��)
	auto axisY = Quaternion::AngleAxis(mAngleAxis.y, AsoUtility::AXIS_Y);
	auto localRotY = localRot.Mult(axisY);

	// �e�̉�]���q�̉�]�ɑ������Ă���O��ŁA����v�Z������]��������
	mTransformBattery.quaRot = mTransformBattery.quaRot.Mult(localRotY);
	mTransformBattery.Update();

	Quaternion localRot2;
	auto axisX = Quaternion::AngleAxis(mAngleAxis.x, AsoUtility::AXIS_X);
	auto localRotX = localRot2.Mult(axisX);
	mTransformBarrel.pos = mTransformBattery.pos;
	mTransformBarrel.quaRot = mTransformBattery.quaRot;
	mTransformBarrel.quaRot = mTransformBarrel.quaRot.Mult(localRotX);
	mTransformBarrel.Update();
}

void Turret::Draw()
{
	if (isDead_) return;

	MV1DrawModel(mTransformBattery.modelId);
	MV1DrawModel(mTransformBarrel.modelId);

	//DrawSphere3D(mTransformBarrel.pos, 200.0f, 16, 0xffffff, 0xffffff, false);
}

bool Turret::IsDead()
{
	return isDead_;
}

bool Turret::CollCheck(const VECTOR& start, const VECTOR& end, float radius)
{
	if (HitCheck_Sphere_Capsule(mTransformBarrel.pos, 200.0f, start, end, radius))
	{
		isDead_ = true;
		return true;
	}
	return false;
}

Transform& Turret::GetTransform()
{
	return mTransformBarrel;
}
