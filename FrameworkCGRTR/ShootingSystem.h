#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include <vector>

class Projectile : public GameObject
{
public:
	Projectile(Mesh* mesh, const glm::vec3& world_position, const glm::vec3& velocity_direction);
	void Update(float dt);
	float GetTime() const
	{
		return time;
	}
private:
	glm::vec3 velocity_direction;
	float speed = 4.0f;
	float time = 0.0f;
};

class ShootingSystem
{
public:
	ShootingSystem(class Camera* camera, std::vector<GameObject> scene_objects, float projectile_radius = 0.01f);
	void Update(class Window* window, float dt);
private:
	Camera* camera;
	Mesh sphere;
	float projectile_radius;
	std::vector<GameObject> scene_objects;
	std::vector<Projectile> projectiles;
};