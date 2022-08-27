#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	struct Dimensions
	{
		int width;
		int height;
	};
public:
	Window(int width, int height, const std::string& name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	GLFWwindow* GetWindow() const
	{
		return window;
	}
	Dimensions GetDimensions()
	{
		return { width, height };
	}
	static void Resize(GLFWwindow* window, int width, int height);
private:
	int width;
	int height;
	std::string name;
	GLFWwindow* window = nullptr;
};