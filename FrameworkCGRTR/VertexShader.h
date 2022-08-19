#pragma once

#include "Bindable.h"
#include <memory>

class VertexShader : public Bindable
{
public:
	VertexShader() = delete;
	~VertexShader();
	static std::shared_ptr<VertexShader> Resolve(const std::string& fs_path);
	GLuint GetVertexShaderID() const
	{
		return vs;
	}
private:
	VertexShader(const std::string& vs_path);
	void Bind() override;
private:
	std::string vs_path;
	GLuint vs;
};