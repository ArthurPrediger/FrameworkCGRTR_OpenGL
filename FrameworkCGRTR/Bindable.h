#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Bindable
{
public:
	Bindable(const std::string& type)
		:
		type(type)
	{}
	virtual ~Bindable() = default;
	virtual void Bind() = 0;
	const std::string& GetType() const
	{
		return type;
	}
private:
	std::string type;
};