#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	friend class App;
public:
	Camera();
	void Update(class Window* window, float dt);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewProjectionMatrix();
	const glm::vec3& GetPosition() const
	{
		return position;
	}
	const glm::vec3& GetForwardVector() const
	{
		return forward;
	}
	const glm::vec3& GetRightVector() const
	{
		return right;
	}
	const glm::vec3& GetUpVector() const
	{
		return up;
	}
private:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	float pitch;
	float yaw;

	std::pair<double, double> prevMousePos;

	glm::mat4 view;
	float moveSpeed;
	float rotationSpeed;
	float fov;
	float aspectRatio;
	glm::mat4 projection;
};