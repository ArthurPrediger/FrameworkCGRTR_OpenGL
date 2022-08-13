#include "FragmentShader.h"
#include "ShaderLoader.h"

FragmentShader::FragmentShader(const std::wstring& fs_path)
	:
	Bindable("FragmentShader")
{
	std::string fragment_shader_str = "";
	LoadShaderFromFile(fs_path, fragment_shader_str);
	const char* fragment_shader = fragment_shader_str.c_str();

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
}

FragmentShader::~FragmentShader()
{
	glDeleteShader(fs);
}

void FragmentShader::Bind()
{
}
