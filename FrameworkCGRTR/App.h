#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <memory>

class App
{
public:
	App();

	void Run();
private:
	std::unique_ptr<Window> window;
};