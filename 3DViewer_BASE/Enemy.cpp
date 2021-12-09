#include "Enemy.h"
#include "AsoUtility.h"
#include "Unit.h"

Enemy::Enemy(SceneManager* manager, Unit* unit):mSceneManager(manager),mUnit(unit)
{
    mModelID = MV1LoadModel("Model/Human.mv1");
    mPos = { 200.0f,0.0f,200.0f };
    MV1SetPosition(mModelID, mPos);

    mAngle = 20.0f;
    mRange = 500.0f;
}

void Enemy::Init()
{
}

void Enemy::Update()
{
    VECTOR distance;
    VECTOR pPos = mUnit->GetPos();
    VectorSub(&distance, &pPos,&mPos);
    float d = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;

    if (d > mRange * mRange)
    {
        MV1SetMaterialDifColor(mModelID, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        return;
    }

    VECTOR f = GetForward();
    VECTOR u;
    VectorNormalize(&u, &distance);
    float theta = acosf(VDot(f, u));

    if (AsoUtility::Rad2DegF(theta) > mAngle)
    {
        MV1SetMaterialDifColor(mModelID, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        return;
    }

    MV1SetMaterialDifColor(mModelID, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
}

void Enemy::Draw()
{
    MV1DrawModel(mModelID);

    float angle = (mAngle * 2.0f) / 20.0f;
    VECTOR rot, pos2, pos3;
    pos2 = GetForward();
    VectorRotationY(&rot, &pos2, AsoUtility::Deg2RadF(mAngle));
    VectorScale(&pos2, &rot, mRange);

    for (int i = 0; i < 20; i++)
    {
        VECTOR pos3;
        
        VectorRotationY(&pos3, &pos2, AsoUtility::Deg2RadF(-angle));

        VECTOR right, left;

        VectorAdd(&right, &mPos, &pos2);
        VectorAdd(&left, &mPos, &pos3);

        DrawTriangle3D(mPos, right, left, 0xffffff, true);
        pos2 = pos3;
    }

    
}

void Enemy::Release()
{
}

VECTOR Enemy::GetPos() const
{
    return VECTOR();
}

VECTOR Enemy::GetForward() const
{
    VECTOR ret;
    VECTOR forward = { 0.0,0.0,-1.0f };

    VectorRotationY(&ret, &forward, -mAngles.y);

    return ret;
}
