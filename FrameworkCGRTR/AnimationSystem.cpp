#include "AnimationSystem.h"
#include "GameObject.h"
#include "SplitString.h"

#include <string>
#include <fstream>
#include <exception>

AnimationSystem::AnimationSystem(std::vector<GameObject>* scene_objects)
	:
	scene_objects(scene_objects),
	cur_key_points({ 0, 1 })
{
	std::ifstream file("trail.txt");

	if (file.is_open())
	{
		while(!file.eof())
		{
			std::string point = "";
			std::getline(file, point);

			auto p_components = Split(point, ' ');

			if(p_components.size() == 3)
				key_points.emplace_back(std::stof(p_components[0]), std::stof(p_components[1]), std::stof(p_components[2]));
		}

		if(key_points.size() > 0)
			cur_pos = key_points.front();

		for (auto& object : *scene_objects)
		{
			if (object.description & GameObjectDescriptor::animated)
			{
				object.SetWorldPosition(cur_pos);
			}
		}
	}
	else
	{
		throw std::runtime_error("Couldn't open file with keys points to the AnimationSystem.");
	}
}

void AnimationSystem::Update(float dt)
{
	glm::vec3 new_pos = cur_pos;

	glm::vec3 direction(0.0f);
	while (true)
	{
		direction = glm::normalize(key_points[cur_key_points.second] - key_points[cur_key_points.first]);
		new_pos += animation_speed * dt * direction;

		if (glm::dot(direction, key_points[cur_key_points.second] - new_pos) < 0)
		{
			if (++cur_key_points.second >= key_points.size()) cur_key_points.second = 0;
			new_pos = cur_pos;
		}
		else
		{
			cur_pos = new_pos;
			cur_key_points.first = cur_key_points.second - 1;
			if (cur_key_points.first < 0 || cur_key_points.first >= key_points.size()) cur_key_points.first = 0;
			break;
		}
	}

	for (auto& object : *scene_objects)
	{
		if (object.description & GameObjectDescriptor::animated)
		{
			object.SetWorldPosition(cur_pos);

			auto theta = glm::degrees(acos(glm::dot({ 0.0f, 0.0f, 1.0f }, direction)));
			if (direction.x < 0)
				theta = glm::degrees(glm::two_pi<float>()) - theta;

			auto phi = glm::degrees(asin(glm::dot({ 0.0f, 1.0f, 0.0f }, direction)));
			if (direction.z > 0) phi *= -1.0f;

			const auto& default_rot = object.GetDefaultWorldRotation();
			object.SetWorldRotation({ default_rot.x + phi, default_rot.y, default_rot.z + theta });
		}
	}
}
