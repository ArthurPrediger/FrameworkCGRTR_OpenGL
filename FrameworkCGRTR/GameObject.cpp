#include "GameObject.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture2D.h"
#include "Cube.h"
#include "UniformLocation.h"
#include <iostream>

GameObject::GameObject(Mesh* mesh)
	:
	mesh(mesh),
	transform(std::make_shared<glm::mat4>(glm::identity<glm::mat4>()))
{
	std::shared_ptr<VertexShader> vs = VertexShader::Resolve("TextureVS.txt");
	//std::shared_ptr<VertexShader> vs = VertexShader::Resolve("SimpleVertexShader.txt");

	std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("TextureFS.txt");
	//std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("SimpleFragmentShader.txt");

	sp = ShaderProgram::Resolve(vs, fs);

	auto group = mesh->QueryGroup(0);
	for (size_t i = 0; group != nullptr; i++, group = mesh->QueryGroup(i))
	{
		group->AddBindable(vs);

		group->AddBindable(fs);

		group->AddBindable(sp);
	}

	std::shared_ptr<UniformLocation<glm::mat4>> unifLoc = UniformLocation<glm::mat4>::Resolve(sp, "transform", transform);
	sp->AddUniformLocationBindable(unifLoc);
}
void GameObject::SetTransform(const glm::mat4& transform)
{
	*(this->transform) = transform;
}

void GameObject::Draw(float dt)
{
	mesh->Draw();
}