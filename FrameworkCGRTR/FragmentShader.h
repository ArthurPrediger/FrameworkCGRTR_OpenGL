#pragma once

#include "Bindable.h"
#include <memory>

class FragmentShader : public Bindable
{
public:
	FragmentShader() = delete;
	~FragmentShader();
	static std::shared_ptr<FragmentShader> Resolve(const std::string& fs_path);
	GLuint GetFragmentShaderID() const
	{
		return fs;
	}
private:
	FragmentShader(const std::string& fs_path);
	void Bind() override;
private:
	std::string fs_path;
	GLuint fs;
};