#include "VertexShader.h"
#include "ShaderLoader.h"
#include "BindableSet.h"

VertexShader::VertexShader(const std::string& vs_path)
	:
	Bindable("VertexShader", BindType::OnInitialization),
	vs_path(vs_path),
	vs(NULL)
{}

VertexShader::~VertexShader()
{
	glDeleteShader(vs);
}

void VertexShader::Bind()
{
	std::string vertex_shader_str = "";
	LoadShaderFromFile(vs_path, vertex_shader_str);
	const char* vertex_shader = vertex_shader_str.c_str();

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);
}

std::shared_ptr<VertexShader> VertexShader::Resolve(const std::string& vs_path)
{
	auto pair = BindableSet::Resolve<VertexShader>(vs_path);
	if (!pair.first)
	{
		pair.second->Bind();
	}
	return pair.second;
}

std::string VertexShader::GetUniqueID(const std::string& vs_path)
{
	return "VS_" + vs_path;
};
