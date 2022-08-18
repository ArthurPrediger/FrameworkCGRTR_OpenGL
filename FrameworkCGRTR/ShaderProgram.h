#pragma once

#include "Bindable.h"
#include <memory>

class ShaderProgram : public Bindable
{
public:
	ShaderProgram(const class VertexShader& vs, const class FragmentShader& fs);
	~ShaderProgram();
	virtual void Bind() override;
	virtual const std::string& GetCode() const override
	{
		return code;
	}
public:
	void Setup();
private:
	std::string code;
	const VertexShader& vs;
	const FragmentShader& fs;
	GLuint sp;
};