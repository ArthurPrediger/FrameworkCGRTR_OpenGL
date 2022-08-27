#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "BindableSet.h"
#include <stdexcept>

ShaderProgram::ShaderProgram(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs)
	:
	Bindable("ShaderProgram", BindType::OnDraw),
	name("SP_" + VertexShader::GetUniqueID(vs->GetFilePath()) + "_" + FragmentShader::GetUniqueID(fs->GetFilePath())),
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
	auto pair = BindableSet::Resolve<ShaderProgram>(vs, fs);
	if (!pair.first)
	{
		pair.second->Create();
	}
	return pair.second;
}

std::string ShaderProgram::GetUniqueID(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs)
{
	return "SP_" + VertexShader::GetUniqueID(vs->GetFilePath()) + "_" + FragmentShader::GetUniqueID(fs->GetFilePath());
};

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
		for (auto& unifLoc : uniformLocations)
		{
			if (unifLoc->GetName() == uniformLocation->GetName())
				return;
		}
		uniformLocations.push_back(uniformLocation);
	}
}
