#include "FragmentShader.h"
#include "ShaderLoader.h"
#include "BindableSet.h"

FragmentShader::FragmentShader(const std::string& fs_path)
	:
	Bindable("FragmentShader", BindType::OnInitialization),
	fs_path(fs_path),
	fs(NULL)
{}

FragmentShader::~FragmentShader()
{
	glDeleteShader(fs);
}

void FragmentShader::Bind()
{
	std::string fragment_shader_str = "";
	LoadShaderFromFile(fs_path, fragment_shader_str);
	const char* fragment_shader = fragment_shader_str.c_str();

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
}

std::shared_ptr<FragmentShader> FragmentShader::Resolve(const std::string& fs_path)
{
	auto pair = BindableSet::Resolve<FragmentShader>(fs_path);
	if (!pair.first)
	{
		pair.second->Bind();
	}
	return pair.second;
}

std::string FragmentShader::GetUniqueID(const std::string& fs_path)
{
	return "FS_" + fs_path;
};
