#include "GameObject.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture2D.h"
#include "UniformLocation.h"
#include "Cube.h"
#include <iostream>

GameObject::GameObject(Mesh* mesh, const glm::vec3& world_position, const std::string& vs_name, const std::string& fs_name, 
	const glm::vec3& world_rotation, float scale)
	:
	mesh(mesh),
	transform (std::make_shared<glm::mat4>(glm::identity<glm::mat4>())),
	world_position(world_position),
	world_rotation(world_rotation),
	scale(scale)
{
	std::shared_ptr<VertexShader> vs = VertexShader::Resolve(vs_name);
	
	std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve(fs_name);
	
	sp = ShaderProgram::Resolve(vs, fs);

	auto group = mesh->QueryGroup(0);
	for (size_t i = 0; group != nullptr; i++, group = mesh->QueryGroup(i))
	{
		group->AddBindable(vs);

		group->AddBindable(fs);

		group->AddBindable(sp);
	}

	std::shared_ptr<UniformLocation<glm::mat4>> unifLoc_transform = UniformLocation<glm::mat4>::Resolve(sp, "transform", transform);
	sp->AddUniformLocationBindable(unifLoc_transform);
}

void GameObject::Draw(float dt, const glm::mat4& view, const glm::mat4& projection)
{
	glm::mat4 world = glm::translate(glm::identity<glm::mat4>(), world_position);
	world = glm::rotate(world, world_rotation.x, { 1.0f, 0.0f, 0.0f });
	world = glm::rotate(world, world_rotation.y, { 0.0f, 1.0f, 0.0f });
	world = glm::rotate(world, world_rotation.z, { 0.0f, 0.0f, 1.0f });
	world = glm::scale(world, { scale, scale, scale });

	*transform = projection * view * world;
	mesh->Draw();
}