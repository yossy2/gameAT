#pragma once

/// <summary>
/// プログラム起動からの時間を計測するクラス
/// 前フレームからの経過時間を記憶する
/// </summary>
class TimeCount
{
private:
	// 生成禁止
	TimeCount();

	// コピー、代入禁止
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
	/// ゲームが起動してからの時間を返す
	/// </summary>
	/// <returns></returns>
	static int GetCount();

	/// <summary>
	/// 前フレームからの経過時間を返す
	/// </summary>
	/// <returns>前フレームからの経過時間（1秒を超えたら0を返す）</returns>
	static float GetDeltaTime();
	static void Update();
	~TimeCount();
};

