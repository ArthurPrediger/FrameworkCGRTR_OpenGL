#pragma once

#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(const std::wstring& vs_path);
	~VertexShader();
	virtual void Bind() override;
	GLuint GetVertexShaderID() const
	{
		return vs;
	}
private:
	GLuint vs;
};