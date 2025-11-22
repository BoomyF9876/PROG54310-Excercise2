#include "WindowController.h"

WindowController::~WindowController()
{
	if (window != nullptr)
	{
		glfwTerminate();
		window = nullptr;
	}
}

void WindowController::Create(int _width, int _height)
{
	if (_width == -1 || _height == -1)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		resolution = Resolution(mode->width, mode->height);
	}
	else
	{
		resolution = Resolution(_width, _height);
	}

}

void WindowController::NewWindow()
{
	M_ASSERT(glfwInit(), "Failed");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	Resolution r = WindowController::GetResolution();
	window = glfwCreateWindow(r.width, r.height, "Sample", NULL, NULL);
	M_ASSERT((window != nullptr), "Failed");
	glfwMakeContextCurrent(window);

}
