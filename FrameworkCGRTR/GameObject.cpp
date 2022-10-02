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

GameObject::GameObject(Mesh* mesh, const std::string& vs_name, const std::string& fs_name, const glm::vec3& world_position,
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

	SetCollisonParameters();
}

void GameObject::Draw(float dt, const glm::mat4& view, const glm::mat4& projection)
{
	glm::mat4 world = glm::translate(glm::identity<glm::mat4>(), world_position);
	world = glm::rotate(world, glm::radians(world_rotation.x), { 1.0f, 0.0f, 0.0f });
	world = glm::rotate(world, glm::radians(world_rotation.y), { 0.0f, 1.0f, 0.0f });
	world = glm::rotate(world, glm::radians(world_rotation.z), { 0.0f, 0.0f, 1.0f });
	world = glm::scale(world, { scale, scale, scale });

	collison_center = glm::vec3(world * glm::vec4(collison_center_no_transform, 1.0f));
	collison_radius = collison_radius_no_transform * scale;

	*transform = projection * view * world;
	mesh->Draw();
}

void GameObject::SetCollisonParameters()
{
	const auto& vertices = mesh->GetVertices().vertsPos;

	glm::vec3 high_extrem = { 0.0f, 0.0f, 0.0f }, low_extrem = { 0.0f, 0.0f, 0.0f };

	for (const auto& vertex : vertices)
	{
		high_extrem.x = std::max(high_extrem.x, vertex.x);
		high_extrem.y = std::max(high_extrem.y, vertex.y);
		high_extrem.z = std::max(high_extrem.z, vertex.z);
		low_extrem.x = std::min(low_extrem.x, vertex.x);
		low_extrem.y = std::min(low_extrem.y, vertex.y);
		low_extrem.z = std::min(low_extrem.z, vertex.z);
	}

	glm::vec3 diff = high_extrem - low_extrem;
	collison_radius_no_transform = std::max(std::max(diff.x, diff.y), diff.z) / 2.0f;
	collison_center_no_transform = (high_extrem + low_extrem) / 2.0f;
}