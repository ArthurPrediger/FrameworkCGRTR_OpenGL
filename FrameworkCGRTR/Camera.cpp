#include "Camera.h"
#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>

Camera::Camera()
	:
	position({ 0.0f, 0.0f, 0.0f }),
	forward({ 0.0f, 0.0f, -1.0f }),
	up({ 0.0f, 1.0f, 0.0f }),
	right(glm::cross(glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f })),
	pitch(0.0f),
	yaw(-glm::half_pi<float>()),
	moveSpeed(10.0f),
	rotationSpeed(glm::pi<float>() / 32.0f),
	fov(50.0f),
	aspectRatio(16.0f / 9.0f),
	view(glm::identity<glm::mat4>()),
	projection(glm::identity<glm::mat4>()),
	prevMousePos({ 0.0f, 0.0f })
{};

void Camera::Update(Window* pWindow, float dt)
{
	aspectRatio = (float)pWindow->GetDimensions().width / (float)pWindow->GetDimensions().height;
	GLFWwindow* window = pWindow->GetWindow();

	double xPos = 0.0f, yPos = 0.0f;
	glfwGetCursorPos(window, &xPos, &yPos);

	if (xPos != prevMousePos.first || yPos != prevMousePos.second)
	{
		yaw -= float(prevMousePos.first - xPos) * rotationSpeed * dt;
		pitch += float(prevMousePos.second - yPos) * rotationSpeed * dt;
		prevMousePos.first = xPos;
		prevMousePos.second = yPos;
		
		yaw = fmod(yaw, glm::two_pi<float>());
		pitch = std::clamp(pitch, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f);
		
		forward.x = cosf(pitch) * cosf(yaw);
		forward.y = sinf(pitch);
		forward.z = cosf(pitch) * sinf(yaw);
		forward = glm::normalize(forward);
		
		right = glm::normalize(glm::cross(forward, { 0.0f, 1.0f, 0.0f }));
		up = glm::normalize(glm::cross(right, forward));
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += forward * (moveSpeed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= forward * (moveSpeed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += right * (moveSpeed * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= right * (moveSpeed * dt);
	}
};

glm::mat4 Camera::GetViewMatrix()
{
	view = glm::identity<glm::mat4>();
	view = glm::lookAt(position, position + forward, up);
	return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	projection = glm::identity<glm::mat4>();
	projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);

	return projection;
};

glm::mat4 Camera::GetViewProjectionMatrix()
{
	return GetProjectionMatrix() * GetViewMatrix();
};
