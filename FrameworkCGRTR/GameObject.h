#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>

class GameObject
{
public:
	GameObject(class Mesh* mesh, const std::string& vs_name, const std::string& fs_name, const glm::vec3& world_position,
		const glm::vec3& world_rotation = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f);
	void Draw(float dt, const glm::mat4& view, const glm::mat4& projection);
	const glm::vec3& GetWorldPosition() const
	{
		return world_position;
	}
	void SetWorldPosition(const glm::vec3& position)
	{
		world_position = position;
	}

private:
	void SetCollisonParameters();

public:
	glm::vec3 collison_center = glm::vec3(0.0f);
	float collison_radius = 0.0f;
	bool is_destructible = false;

private:
	glm::vec3 collison_center_no_transform = glm::vec3(0.0f);
	float collison_radius_no_transform = 0.0f;

private:
	Mesh* mesh;
	std::shared_ptr<class ShaderProgram> sp;
	std::shared_ptr<glm::mat4> transform;
	glm::vec3 world_position;
	glm::vec3 world_rotation;
	float scale;
};