#pragma once

#include "Bindable.h"
#include <memory>

class FragmentShader : public Bindable
{
public:
	FragmentShader(const std::string& fs_path);
	FragmentShader() = delete;
	~FragmentShader();
	static std::shared_ptr<FragmentShader> Resolve(const std::string& fs_path);
	static std::string GetUniqueID(const std::string& fs_path);
	GLuint GetFragmentShaderID() const
	{
		return fs;
	}
	const std::string& GetFilePath() const
	{
		return fs_path;
	}
private:
	void Bind() override;
private:
	std::string fs_path;
	GLuint fs;
};