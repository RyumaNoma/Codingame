#pragma once
#include <chrono>

namespace util
{
	// std::chronoのラッパー
	// あまり速くない
	class Timer
	{
	private:
		std::chrono::system_clock::time_point start_;
	public:
		Timer();

		// 開始時間のリセット．
		void Reset();

		// ミリ秒単位で経過時間を求める
		// 前回Reset()を呼び出してからの経過時間
		std::chrono::milliseconds::rep ElapsedMilliseconds() const;

		// マイクロ秒単位で経過時間を求める
		//前回Reset()を呼び出してからの経過時間
		std::chrono::microseconds::rep ElapsedMicroseconds() const;
	};
}