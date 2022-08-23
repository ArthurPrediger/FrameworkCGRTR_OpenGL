#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "BindableSet.h"
#include <stdexcept>

ShaderProgram::ShaderProgram(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs)
	:
	Bindable("ShaderProgram", "SP_" + vs->GetUniqueID() + "_" + fs->GetUniqueID(), BindType::OnDraw),
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

	for (auto& unifLocs : uniformLocations)
	{
		unifLocs->Bind();
	}
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

void ShaderProgram::AddUniformLocationBindable(std::shared_ptr<Bindable> uniformLocation)
{
	if (uniformLocation->GetType() != "UniformLocation")
	{
		throw std::runtime_error("Trying to add bindable different from UniformLocation to ShaderProgram!");
	}
	else
	{
		uniformLocations.push_back(uniformLocation);
	}
}
