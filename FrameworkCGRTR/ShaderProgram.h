#pragma once

#include "Bindable.h"

class ShaderProgram : public Bindable
{
public:
	ShaderProgram(GLuint vs, GLuint fs);
	~ShaderProgram();
	virtual void Bind() override;
private:
	GLuint sp;
	GLuint vs;
	GLuint fs;
};