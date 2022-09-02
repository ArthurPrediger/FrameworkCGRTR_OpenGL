#pragma once

#include "Mesh.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "UniformLocation.h"
#include "Cube.h"
#include <iostream>

class TestModel
{
public:
	TestModel(Mesh* mesh)
		:
		mesh(mesh),
		transform(std::make_shared<glm::mat4>(glm::identity<glm::mat4>()))
	{
		std::shared_ptr<VertexShader> vs = VertexShader::Resolve("SimpleVertexShader.txt");

		std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("SimpleFragmentShader.txt");

		sp = ShaderProgram::Resolve(vs, fs);

		auto group = mesh->QueryGroup(0);
		for (size_t i = 0; group != nullptr; i++, group = mesh->QueryGroup(i))
		{
			group->AddBindable(vs);

			group->AddBindable(fs);

			group->AddBindable(sp);

			std::shared_ptr<VBO> vbo = VBO::Resolve(std::move(mesh->GetVerticesFromGroup(i)), group->GetName() + std::to_string(i));
			group->AddBindable(vbo);

			std::shared_ptr<VAO> vao = VAO::Resolve({ vbo });
			group->AddBindable(vao);
		}

		std::shared_ptr<UniformLocation<glm::mat4>> unifLoc = UniformLocation<glm::mat4>::Resolve(sp, "transform", transform);
		sp->AddUniformLocationBindable(unifLoc);
	}
	void Draw(float dt)
	{
		mesh->Draw();
	}
public:
	Mesh* mesh;
	std::shared_ptr<ShaderProgram> sp;
	std::shared_ptr<glm::mat4> transform = nullptr;
	float angle = 0;
};