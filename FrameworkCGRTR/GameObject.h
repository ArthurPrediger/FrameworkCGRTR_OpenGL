#pragma once

#include "Mesh.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "UniformLocation.h"
#include "Texture2D.h"
#include "Cube.h"
#include <iostream>

class GameObject
{
public:
	GameObject(Mesh* mesh)
		:
		mesh(mesh),
		transform(std::make_shared<glm::mat4>(glm::identity<glm::mat4>()))
	{
		std::shared_ptr<VertexShader> vs = VertexShader::Resolve("TextureVS.txt");

		std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("TextureFS.txt");

		sp = ShaderProgram::Resolve(vs, fs);

		std::shared_ptr<Texture2D> text = Texture2D::Resolve("../3dModels/trout/trout.png");

		auto group = mesh->QueryGroup(0);
		for (size_t i = 0; group != nullptr; i++, group = mesh->QueryGroup(i))
		{
			group->AddBindable(vs);

			group->AddBindable(fs);

			group->AddBindable(sp);

			group->AddBindable(text);
		}

		std::shared_ptr<UniformLocation<glm::mat4>> unifLoc = UniformLocation<glm::mat4>::Resolve(sp, "transform", transform);
		sp->AddUniformLocationBindable(unifLoc);
	}
	void SetTransform(const glm::mat4& transform)
	{
		*(this->transform) = transform;
	}
	void Draw(float dt)
	{
		mesh->Draw();
	}
private:
	Mesh* mesh;
	std::shared_ptr<ShaderProgram> sp;
	std::shared_ptr<glm::mat4> transform = nullptr;
};