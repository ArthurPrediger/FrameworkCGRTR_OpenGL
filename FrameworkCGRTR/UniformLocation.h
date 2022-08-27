#pragma once

#include "Bindable.h"
#include "BindableSet.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <memory>
#include <stdexcept>

template<typename T>
class UniformLocation : public Bindable
{
	friend class ShaderProgram;
public:
	UniformLocation(std::shared_ptr<ShaderProgram> sp, const std::string& unifLocName, std::shared_ptr<T>& unifLocData)
		:
		Bindable("UniformLocation", BindType::OnDraw),
		spID(sp->GetShaderProgramID()),
		unifLocName(unifLocName),
		unifLocData(unifLocData)
	{};
	UniformLocation() = delete;
	~UniformLocation() = default;
	static std::shared_ptr<UniformLocation<T>> Resolve(std::shared_ptr<ShaderProgram> sp, const std::string& unifLocName, std::shared_ptr<T>& unifLocData)
	{
		auto pair = BindableSet::Resolve<UniformLocation>(sp, unifLocName, unifLocData);
		if (pair.first)
		{
			unifLocData = pair.second->unifLocData;
		}
		return pair.second;
	};
	static std::string GetUniqueID(std::shared_ptr<ShaderProgram> sp, const std::string& unifLocName, std::shared_ptr<T> unifLocData)
	{
		return "UN_" + unifLocName + "_" + sp->GetName();
	};
	std::shared_ptr<T> GetPointerToData() const
	{
		return unifLocData;
	}
	const std::string& GetName() const override
	{
		return unifLocName;
	}
private:
	void Bind() override
	{
		throw std::runtime_error("Unsupported template type");
	};
private:
	GLuint spID;
	std::string unifLocName;
	std::shared_ptr<T> unifLocData;
};

template<> void UniformLocation<float>::Bind()
{
	int floatLocation = glGetUniformLocation(spID, unifLocName.c_str());
	glUniform1f(floatLocation, *unifLocData);
};
template<> void UniformLocation<glm::vec4>::Bind()
{
	int vec4Location = glGetUniformLocation(spID, unifLocName.c_str());
	glUniform4fv(vec4Location, 1, glm::value_ptr(*unifLocData));
};
template<> void UniformLocation<glm::mat4>::Bind()
{
	int mat4Location = glGetUniformLocation(spID, unifLocName.c_str());
	glUniformMatrix4fv(mat4Location, 1, GL_FALSE, glm::value_ptr(*unifLocData));
};