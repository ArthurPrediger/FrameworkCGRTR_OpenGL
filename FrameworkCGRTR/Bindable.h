#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <assert.h>

class Bindable
{
public:
	enum class BindType
	{
		OnInitialization,
		OnDraw
	};
public:
	Bindable(const std::string& type, const BindType& bind_type)
		:
		type(type),
		bind_type(bind_type)
	{}
	virtual ~Bindable() = default;
	virtual void Bind() = 0;
	virtual std::string GetUniqueID()
	{
		assert(false);
		return "";
	};
	const std::string& GetType() const
	{
		return type;
	}
	virtual const std::string& GetName() const
	{
		return type;
	}
	const BindType& GetBindType() const
	{
		return bind_type;
	}
private:
	std::string type;
	BindType bind_type;
};