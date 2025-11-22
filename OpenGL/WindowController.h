#pragma once

#ifndef _WINDOWCONTROLLER_H_
#define _WINDOWCONTROLLER_H_

#include "StandardIncludes.h"

class WindowController
{
	GLFWwindow* window = nullptr;
public:
	static WindowController& GetInstance()
	{
		static WindowController instance;
		return instance;
	}

	void Create(int _width = -1, int _height = -1);

	GLFWwindow* GetWindow()
	{
		if (window == nullptr) {
			NewWindow();
		}
		return window;
	}

	void NewWindow();
	Resolution& GetResolution() { return resolution; }
private:
	WindowController() = default;
	~WindowController();

	Resolution resolution = { 1280, 768 };
};

#endif

