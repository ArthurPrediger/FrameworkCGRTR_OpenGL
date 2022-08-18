#pragma once

#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(const std::string& vs_path);
	~VertexShader();
	virtual void Bind() override;
	virtual const std::string& GetCode() const override
	{
		return vs_path;
	}
	GLuint GetVertexShaderID() const
	{
		return vs;
	}
private:
	std::string vs_path;
	GLuint vs;
};