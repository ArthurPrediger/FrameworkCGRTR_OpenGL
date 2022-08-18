#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"

ShaderProgram::ShaderProgram(const VertexShader& vs, const FragmentShader& fs)
	:
	Bindable("ShaderProgram"),
	code(vs.GetCode() + fs.GetCode()),
	vs(vs),
	fs(fs),
	sp(NULL)
{}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(sp, vs.GetVertexShaderID());
	glDetachShader(sp, fs.GetFragmentShaderID());
	glDeleteProgram(sp);
}

void ShaderProgram::Bind()
{
	glUseProgram(sp);
}

void ShaderProgram::Setup()
{
	sp = glCreateProgram();
	glAttachShader(sp, vs.GetVertexShaderID());
	glAttachShader(sp, fs.GetFragmentShaderID());
	glLinkProgram(sp);
}
