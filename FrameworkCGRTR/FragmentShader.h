#pragma once

#include "Bindable.h"

class FragmentShader : public Bindable
{
public:
	FragmentShader(const std::wstring& fs_path);
	~FragmentShader();
	virtual void Bind() override;
	GLuint GetFragmentShaderID() const
	{
		return fs;
	}
private:
	GLuint fs;
};