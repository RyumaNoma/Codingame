#include "Timer.hpp"

namespace util
{
	Timer::Timer()
	{
		Reset();
	}

	void Timer::Reset()
	{
		start_ = std::chrono::system_clock::now();
	}

	std::chrono::milliseconds::rep Timer::ElapsedMilliseconds() const
	{
		auto now = std::chrono::system_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now - start_).count();
	}

	std::chrono::microseconds::rep Timer::ElapsedMicroseconds() const
	{
		auto now = std::chrono::system_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(now - start_).count();
	}
}