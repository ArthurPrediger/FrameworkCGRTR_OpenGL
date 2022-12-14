#pragma once

#include "Bindable.h"
#include <vector>
#include <memory>

class ShaderProgram : public Bindable
{
public:
	ShaderProgram(std::shared_ptr<class VertexShader> vs, std::shared_ptr<class FragmentShader> fs);
	ShaderProgram() = delete;
	~ShaderProgram();
	void Bind() override;
	static std::shared_ptr<ShaderProgram> Resolve(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs);
	static std::string GetUniqueID(std::shared_ptr<VertexShader> vs, std::shared_ptr<FragmentShader> fs);
	GLuint GetShaderProgramID() const
	{
		return sp;
	}
	const std::string& GetName() const
	{
		return name;
	}
	void AddUniformLocationBindable(std::shared_ptr<Bindable> uniformLocation);
private:
	void Create();
private:
	std::string name;
	std::shared_ptr<VertexShader> vs;
	std::shared_ptr<FragmentShader> fs;
	GLuint sp;
	std::vector<std::shared_ptr<Bindable>> uniformLocations;
};