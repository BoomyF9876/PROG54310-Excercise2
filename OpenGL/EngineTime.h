#pragma once
#ifndef _TIME_H_
#define _TIME_H_

#include <chrono>
#include "Singleton.h"

class Time: public Singleton<Time>
{
private:
	unsigned int frameCount = 0;
	unsigned int fps = 0;
	unsigned int fpsCounter = 0;
	std::chrono::duration<float> deltaTime{};
	std::chrono::time_point<std::chrono::system_clock> beginTime{};
	std::chrono::time_point<std::chrono::system_clock> endTime{};
	std::chrono::time_point<std::chrono::system_clock> fpsTime{};
	std::chrono::duration<float> totalTime{};
	friend class GameController;
	friend class Singleton<Time>;

public:
	float DeltaTime() { return deltaTime.count(); };
	float TotalTime() { return totalTime.count(); };
	unsigned int FrameCount() { return frameCount; };
	unsigned int FPS() { return fps; }
private:
	void Initialize();
	void Update();
	void Destroy();

	inline explicit Time() = default;
	inline ~Time() = default;
};

#endif