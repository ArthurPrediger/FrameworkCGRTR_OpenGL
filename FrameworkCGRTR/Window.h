#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(int width, int height, const std::string& name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	bool WasResized() const
	{
		return wasResized;
	}
	void ResizeHandled()
	{
		wasResized = false;
	}
	GLFWwindow* GetWindow() const
	{
		return window;
	}
private:
	static void Resize(GLFWwindow* window, int width, int height);
private:
	int width;
	int height;
	std::string name;
	bool wasResized = false;
	GLFWwindow* window = nullptr;
};