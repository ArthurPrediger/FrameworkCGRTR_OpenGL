#include "ShootingSystem.h"
#include "Camera.h"
#include "Sphere.h"
#include "Window.h"
#include "Bindable.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "UniformLocation.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/norm.hpp>
#include <algorithm>

Projectile::Projectile(Mesh* mesh, const glm::vec3& world_position, const glm::vec3& velocity_direction)
	:
	GameObject(mesh, world_position),
	velocity_direction(velocity_direction)
{
	std::shared_ptr<VertexShader> vs = VertexShader::Resolve("SimpleVertexShader.txt");
	mesh->QueryGroup(0)->AddBindable(vs);

	std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("SimpleFragmentShader.txt");
	mesh->QueryGroup(0)->AddBindable(fs);

	std::shared_ptr<ShaderProgram> sp = ShaderProgram::Resolve(vs, fs);
	BindShaderProgram(sp);
}

void Projectile::Update(float dt)
{
	SetWorldPosition(GetWorldPosition() + velocity_direction * (dt * speed));
	time += dt;
}

ShootingSystem::ShootingSystem(Camera* camera, std::vector<GameObject>* scene_objects, float projectile_radius)
	:
	camera(camera),
	projectile_radius(projectile_radius),
	sphere(Sphere::GetMesh(projectile_radius)),
	scene_objects(scene_objects),
	projectiles({})
{}

void ShootingSystem::Update(Window* window, float dt)
{
	time += dt;
	if (glfwGetMouseButton(window->GetWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && time > fire_rate)
	{
		projectiles.emplace_back(Projectile{ &sphere, camera->GetPosition(), camera->GetForwardVector() });
		time = 0.0f;
	}

	auto handleCollsion = [](Projectile& projectile, std::vector<GameObject>* objects) {

		size_t index = 0;
		for (auto& object : *objects)
		{
			glm::vec3 diff = projectile.collison_center - object.collison_center;
			float radius_sum = projectile.collison_radius + object.collison_radius;
			if (glm::dot(diff, diff) < (radius_sum * radius_sum) &&
				glm::dot(projectile.GetVelocityDirection(), diff) < 0.0f)
			{
				if (object.is_destructible)
				{
					objects->erase(objects->begin() + index);
					projectile.is_destroyed = true;
				}
				else
				{
					const glm::vec3 normal = glm::normalize(diff);
					const glm::vec3 new_direction = 2 * glm::dot(normal, (-projectile.GetVelocityDirection())) * normal + projectile.GetVelocityDirection();
					projectile.SetVelocityDirection(glm::normalize(new_direction));
				}
				return;
			}
			index++;
		}
	};

	auto view = camera->GetViewMatrix();
	auto projection = camera->GetProjectionMatrix();

	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].Update(dt);

		if (projectiles[i].GetTime() > 10.0f || projectiles[i].is_destroyed) projectiles.erase(projectiles.begin() + i--);
		else
		{
			handleCollsion(projectiles[i], scene_objects);
			projectiles[i].Draw(dt, view, projection);
		}
	}
}