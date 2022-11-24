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

GameObject::GameObject(Mesh* mesh, const glm::vec3& world_position, const glm::vec3& world_rotation, float scale, int description)
	:
	mesh(mesh),
	transform (std::make_shared<glm::mat4>(glm::identity<glm::mat4>())),
	world_transform(std::make_shared<glm::mat4>(glm::identity<glm::mat4>())),
	world_position(world_position),
	world_rotation(world_rotation),
	scale(scale),
	sp(nullptr),
	description(description),
	default_world_rotation(world_rotation)
{
	SetCollisonParameters();
}

void GameObject::BindShaderProgram(std::shared_ptr<ShaderProgram> sp)
{
	this->sp = sp;
	auto group = mesh->QueryGroup(0);
	for (size_t i = 0; group != nullptr; i++, group = mesh->QueryGroup(i))
	{
		group->EraseBindableByType(sp->GetType(), sp->GetBindType());
		group->AddBindable(sp);
	}

	std::shared_ptr<UniformLocation<glm::mat4>> unifLoc_transform = UniformLocation<glm::mat4>::Resolve(sp, "transform", transform);
	sp->AddUniformLocationBindable(unifLoc_transform);

	std::shared_ptr<UniformLocation<glm::mat4>> unifLoc_world_transform = UniformLocation<glm::mat4>::Resolve(sp, "world", world_transform);
	sp->AddUniformLocationBindable(unifLoc_world_transform);
}

void GameObject::Draw(float dt, const glm::mat4& view, const glm::mat4& projection)
{
	*world_transform = glm::translate(glm::identity<glm::mat4>(), world_position);
	*world_transform = glm::rotate(*world_transform, glm::radians(world_rotation.x), { 1.0f, 0.0f, 0.0f });
	*world_transform = glm::rotate(*world_transform, glm::radians(world_rotation.y), { 0.0f, 1.0f, 0.0f });
	*world_transform = glm::rotate(*world_transform, glm::radians(world_rotation.z), { 0.0f, 0.0f, 1.0f });
	*world_transform = glm::scale(*world_transform, { scale, scale, scale });

	collison_center = glm::vec3(*world_transform * glm::vec4(collison_center_no_transform, 1.0f));
	collison_radius = collison_radius_no_transform * scale;

	*transform = projection * view * *world_transform;
	mesh->Draw();
}

void GameObject::SetCollisonParameters()
{
	if (description & GameObjectDescriptor::collidable || description & GameObjectDescriptor::destructible)
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
	else
	{
		collison_radius_no_transform = 0.0f;
		collison_center_no_transform = glm::vec3(0);
	}
}