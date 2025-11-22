#include "EngineTime.h"

void Time::Update()
{
	endTime = std::chrono::system_clock().now();
	
	fpsCounter++;
	std::chrono::duration<float> value = (endTime - fpsTime);
	if (value.count() >= 1.0f)
	{
		fps = fpsCounter;
		fpsCounter = 0;
		fpsTime = endTime;
	}
	
	deltaTime = endTime - beginTime;
	beginTime = endTime;
	totalTime += deltaTime;
	frameCount++;
}

void Time::Initialize()
{
	beginTime = std::chrono::system_clock().now();
	endTime = std::chrono::system_clock().now();
	fpsTime = std::chrono::system_clock().now();

	deltaTime = std::chrono::duration<float>(0);
	totalTime = std::chrono::duration<float>(0);
	frameCount = 0;
}

void Time::Destroy()
{
	DestroyInstance();
}
