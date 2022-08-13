#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(GLuint vs, GLuint fs)
	:
	Bindable("ShaderProgram"),
	vs(vs),
	fs(fs)
{
	sp = glCreateProgram();
	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);
}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(sp, vs);
	glDetachShader(sp, fs);
	glDeleteProgram(sp);
}

void ShaderProgram::Bind()
{
	glUseProgram(sp);
}
