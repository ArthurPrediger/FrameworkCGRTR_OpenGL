#pragma once

#include "Bindable.h"
#include <vector>
#include <memory>

class ShaderProgram : public Bindable
{
public:
	ShaderProgram() = delete;
	~ShaderProgram();
	void Bind() override;
	static std::shared_ptr<ShaderProgram> Resolve(std::shared_ptr<class VertexShader> vs, std::shared_ptr<class FragmentShader> fs);
	GLuint GetShaderProgramID() const
	{
		return sp;
	}
	void AddUniformLocationBindable(std::shared_ptr<Bindable> uniformLocation);
private:
	ShaderProgram(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs);
	void Create();
private:
	std::shared_ptr<VertexShader> vs;
	std::shared_ptr<FragmentShader> fs;
	GLuint sp;
	std::vector<std::shared_ptr<Bindable>> uniformLocations;
};