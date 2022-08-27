#include "Window.h"
#include <stdexcept>

Window::Window(int width, int height, const std::string& name)
	:
	width(width),
	height(height),
	name(name)
{
	if (!glfwInit()) 
	{
		throw std::runtime_error ("ERROR: could not start GLFW3");
	}
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, Resize);

	if (!window) 
	{
		throw std::runtime_error("ERROR: could not open window with GLFW3");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, Window::Resize);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Resize(GLFWwindow* window, int width, int height)
{
	auto pWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	pWindow->width = width;
	pWindow->height = height;
}
