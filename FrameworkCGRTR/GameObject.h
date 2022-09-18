#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class GameObject
{
public:
	GameObject(class Mesh* mesh);
	void SetTransform(const glm::mat4& transform);
	void Draw(float dt);
private:
	Mesh* mesh;
	std::shared_ptr<class ShaderProgram> sp;
	std::shared_ptr<glm::mat4> transform = nullptr;
};