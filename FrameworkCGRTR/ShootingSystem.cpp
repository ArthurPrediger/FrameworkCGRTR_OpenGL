#include "ShootingSystem.h"
#include "Camera.h"
#include "Sphere.h"
#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>

Projectile::Projectile(Mesh* mesh, const glm::vec3& world_position, const glm::vec3& velocity_direction)
	:
	GameObject(mesh, world_position, "SimpleVertexShader.txt", "SimpleFragmentShader.txt"),
	velocity_direction(velocity_direction)
{}

void Projectile::Update(float dt)
{
	SetWorldPosition(GetWorldPosition() + velocity_direction * (dt * speed));
	time += dt;
}

ShootingSystem::ShootingSystem(Camera* camera, std::vector<GameObject> scene_objects, float projectile_radius)
	:
	camera(camera),
	projectile_radius(projectile_radius),
	sphere(Sphere::GetMesh(projectile_radius)),
	scene_objects(scene_objects),
	projectiles({})
{}

void ShootingSystem::Update(Window* window, float dt)
{
	if (glfwGetMouseButton(window->GetWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		projectiles.emplace_back(Projectile{ &sphere, camera->GetPosition(), camera->GetForwardVector() });
	}

	auto view = camera->GetViewMatrix();
	auto projection = camera->GetProjectionMatrix();

	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].Update(dt);
		if (projectiles[i].GetTime() > 10.0f) projectiles.erase(projectiles.begin() + i--);
		else projectiles[i].Draw(dt, view, projection);
	}
}