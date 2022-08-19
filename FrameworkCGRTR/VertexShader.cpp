#include "VertexShader.h"
#include "ShaderLoader.h"
#include "BindableSet.h"

VertexShader::VertexShader(const std::string& vs_path)
	:
	Bindable("VertexShader", "VertexShader_" + vs_path, BindType::OnInitilization),
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

std::shared_ptr<VertexShader> VertexShader::Resolve(const std::string& fs_path)
{
	auto vs = std::shared_ptr<VertexShader>(new VertexShader(fs_path));
	if (BindableSet::Resolve(vs))
	{
		vs->Bind();
	}
	return vs;
}
