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
	glm::mat4 GetViewProjectionMatrix();
private:
	glm::vec3 position;
	glm::vec3 front;
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