#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>

class GameObject
{
public:
	GameObject(class Mesh* mesh, const glm::vec3& world_position, const std::string& vs_name, const std::string& fs_name,
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
	Mesh* mesh;
	std::shared_ptr<class ShaderProgram> sp;
	std::shared_ptr<glm::mat4> transform;
	glm::vec3 world_position;
	glm::vec3 world_rotation;
	float scale;
};