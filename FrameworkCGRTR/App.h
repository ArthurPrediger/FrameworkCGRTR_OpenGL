#pragma once

#include "Window.h"
#include "Timer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

class App
{
public:
	App();

	void Run();
private:
	std::unique_ptr<class Window> window;
	Timer timer{};
};