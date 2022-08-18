#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	float Tick();
private:
	std::chrono::steady_clock::time_point time;
};