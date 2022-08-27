#pragma once

#include "Bindable.h"
#include <memory>

class VertexShader : public Bindable
{
public:
	VertexShader(const std::string& vs_path);
	VertexShader() = delete;
	~VertexShader();
	static std::shared_ptr<VertexShader> Resolve(const std::string& vs_path);
	static std::string GetUniqueID(const std::string& vs_path);
	GLuint GetVertexShaderID() const
	{
		return vs;
	}
	const std::string& GetFilePath() const
	{
		return vs_path;
	}
private:
	void Bind() override;
private:
	std::string vs_path;
	GLuint vs;
};