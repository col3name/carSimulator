#include "stdafx.h"
#include <thread>
#include "Chronometer.h"

float CChronometer::GrabDeltaTime()
{
	auto newTime = std::chrono::system_clock::now();
	auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - m_lastTime);
	m_lastTime = newTime;
	return 0.001f * float(timePassed.count());
};

void CChronometer::WaitNextFrameTime(const std::chrono::milliseconds &framePeriod)
{
	std::chrono::system_clock::time_point nextFrameTime = m_lastTime + framePeriod;
	std::this_thread::sleep_until(nextFrameTime);
}