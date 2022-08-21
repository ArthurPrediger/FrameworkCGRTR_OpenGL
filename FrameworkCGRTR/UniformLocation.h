#pragma once

#include "Bindable.h"
#include "BindableSet.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>

template<typename T>
class UniformLocation : public Bindable
{
	friend class ShaderProgram;
private:
	UniformLocation(std::shared_ptr<class ShaderProgram> sp, const std::string& unifLocName, std::shared_ptr<T> unifLocData)
		:
		Bindable("ShaderProgram", "UN_" + unifLocName + "_" + sp->GetUniqueID(), BindType::OnDraw),
		spID(sp->GetShaderProgramID()),
		unifLocName(unifLocData),
		unifLocData(unifLocData)
	{};
	UniformLocation() = delete;
	~UniformLocation() = default;
	std::shared_ptr<T> GetPointerToData() const
	{
		return unifLocData;
	}
	template<typename float>
	void Bind()
	{
		int floatLocation = glGetUniformLocation(spID, unifLocName.c_str());
		glUniform1f(floatLocation, 1, GL_FALSE, glm::value_ptr(unifLocData));
	}
	template<typename glm::vec4>
	void Bind()
	{
		int vec4Location = glGetUniformLocation(spID, unifLocName.c_str());
		glUniform4fv(vec4Location, 1, GL_FALSE, glm::value_ptr(unifLocData));
	}
	template<typename glm::mat4>
	void Bind()
	{
		int mat4Location = glGetUniformLocation(spID, unifLocName.c_str());
		glUniformMatrix4fv(mat4Location, 1, GL_FALSE, glm::value_ptr(unifLocData));
	}
	void Bind()
	{
		assert("Unsupported template type");
	}
	std::shared_ptr<UniformLocation> Resolve(std::shared_ptr<ShaderProgram> sp, const std::string& unifLocName, std::shared_ptr<T> unifLocData)
	{
		auto uniformLocation = std::shared_ptr<UniformLocation>(new UniformLocation(sp, unifLocName, unifLocData));
		BindableSet::Resolve(uniformLocation);
		return uniformLocation;
	};
private:
	GLuint spID;
	std::string unifLocName;
	std::shared_ptr<T> unifLocData;
};