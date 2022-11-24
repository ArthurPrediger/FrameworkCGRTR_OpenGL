#pragma once

#include <vector>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

class AnimationSystem
{
public:
	AnimationSystem(std::vector<class GameObject>* scene_objects);
	void Update(float dt);
private:
	std::vector<glm::vec3> key_points;
	std::pair<size_t, size_t> cur_key_points;
	glm::vec3 cur_pos = glm::vec3(0);
	float animation_speed = 16.0f;
	std::vector<GameObject>* scene_objects;
};