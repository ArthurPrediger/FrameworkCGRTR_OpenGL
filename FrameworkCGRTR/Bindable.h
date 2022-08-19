#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Bindable
{
public:
	enum class BindType
	{
		OnInitilization,
		OnDraw
	};
public:
	Bindable(const std::string& type, const std::string& uID, const BindType& bind_type)
		:
		type(type),
		uID(uID),
		bind_type(bind_type)
	{}
	virtual ~Bindable() = default;
	virtual void Bind() = 0;
	const std::string& GetUniqueID() const
	{
		return uID;
	};
	const std::string& GetType() const
	{
		return type;
	}
	const BindType& GetBindType() const
	{
		return bind_type;
	}
protected:
	std::string uID;
private:
	std::string type;
	BindType bind_type;
};