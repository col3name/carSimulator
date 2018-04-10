#pragma once

class CChronometer
{
public:
	float GrabDeltaTime();
	void WaitNextFrameTime(const std::chrono::milliseconds& framePeriod);

private:
	std::chrono::system_clock::time_point m_lastTime;
};
