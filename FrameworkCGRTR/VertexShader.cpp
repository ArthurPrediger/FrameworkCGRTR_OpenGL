#include "VertexShader.h"
#include "ShaderLoader.h"

VertexShader::VertexShader(const std::wstring& vs_path)
	:
	Bindable("VertexShader")
{
	std::string vertex_shader_str = "";
	LoadShaderFromFile(vs_path, vertex_shader_str);
	const char* vertex_shader = vertex_shader_str.c_str();

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);
}

VertexShader::~VertexShader()
{
	glDeleteShader(vs);
}

void VertexShader::Bind()
{
}
