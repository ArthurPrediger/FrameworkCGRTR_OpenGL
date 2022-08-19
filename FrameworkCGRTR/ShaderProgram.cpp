#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "BindableSet.h"

ShaderProgram::ShaderProgram(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs)
	:
	Bindable("ShaderProgram", "ShaderProgram_" + vs->GetUniqueID() + "_" + fs->GetUniqueID(), BindType::OnDraw),
	vs(vs),
	fs(fs),
	sp(NULL)
{}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(sp, vs->GetVertexShaderID());
	glDetachShader(sp, fs->GetFragmentShaderID());
	glDeleteProgram(sp);
}

void ShaderProgram::Bind()
{
	glUseProgram(sp);
}

std::shared_ptr<ShaderProgram> ShaderProgram::Resolve(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs)
{
	auto ps = std::shared_ptr<ShaderProgram>(new ShaderProgram(vs, fs));
	if (BindableSet::Resolve(ps))
	{
		ps->Create();
	}
	return ps;
}

void ShaderProgram::Create()
{
	sp = glCreateProgram();
	glAttachShader(sp, vs->GetVertexShaderID());
	glAttachShader(sp, fs->GetFragmentShaderID());
	glLinkProgram(sp);
}
