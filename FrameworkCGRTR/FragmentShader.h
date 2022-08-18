#pragma once

#include "Bindable.h"

class FragmentShader : public Bindable
{
public:
	FragmentShader(const std::string& fs_path);
	~FragmentShader();
	virtual void Bind() override;
	virtual const std::string& GetCode() const override
	{
		return fs_path;
	}
	GLuint GetFragmentShaderID() const
	{
		return fs;
	}
private:
	std::string fs_path;
	GLuint fs;
};