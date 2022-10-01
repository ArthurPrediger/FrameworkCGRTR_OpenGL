#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include <vector>

class Projectile : public GameObject
{
public:
	Projectile(Mesh* mesh, const glm::vec3& world_position, const glm::vec3& velocity_direction);
	void Update(float dt);
	const glm::vec3& GetVelocityDirection() const
	{
		return velocity_direction;
	}
	void SetVelocityDirection(const glm::vec3& direction)
	{
		velocity_direction = direction;
	}
	float GetTime() const
	{
		return time;
	}

public:
	bool is_destroyed = false;

private:
	glm::vec3 velocity_direction;
	float speed = 4.0f;
	float time = 0.0f;
};

class ShootingSystem
{
public:
	ShootingSystem(class Camera* camera, std::vector<GameObject>* scene_objects, float projectile_radius = 0.1f);
	void Update(class Window* window, float dt);
private:
	Camera* camera;
	Mesh sphere;
	float projectile_radius;
	std::vector<GameObject>* scene_objects;
	std::vector<Projectile> projectiles;
	float fire_rate = 0.5f;
	float time = 0.0f;
};