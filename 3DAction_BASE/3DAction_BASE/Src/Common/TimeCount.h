#pragma once

/// <summary>
/// �v���O�����N������̎��Ԃ��v������N���X
/// �O�t���[������̌o�ߎ��Ԃ��L������
/// </summary>
class TimeCount
{
private:
	// �����֎~
	TimeCount();

	// �R�s�[�A����֎~
	TimeCount(const TimeCount&) = delete;
	void operator=(const TimeCount&) = delete;

	int nowCount_;
	float deltaTime_;

	int GetCount_();
	float GetDeltaTime_();
	void Update_();
	static TimeCount& Instance();

public:

	/// <summary>
	/// �Q�[�����N�����Ă���̎��Ԃ�Ԃ�
	/// </summary>
	/// <returns></returns>
	static int GetCount();

	/// <summary>
	/// �O�t���[������̌o�ߎ��Ԃ�Ԃ�
	/// </summary>
	/// <returns>�O�t���[������̌o�ߎ��ԁi1�b�𒴂�����0��Ԃ��j</returns>
	static float GetDeltaTime();
	static void Update();
	~TimeCount();
};

