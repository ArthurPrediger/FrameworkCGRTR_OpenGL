#pragma once

#include "Window.h"
#include "Timer.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

class App
{
public:
	App();

	void Run();
private:
	std::unique_ptr<Window> window;
	Timer timer;
	Camera camera;
};