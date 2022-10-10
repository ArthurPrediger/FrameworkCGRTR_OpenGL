#pragma once

#include "Group.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

void CalculateNormals(const std::vector<glm::vec3>& positions, std::vector<Group::Face>& faces, std::vector<glm::vec3>& normals)
{
	for (auto& face : faces)
	{
		const auto& vec0 = positions[face.posIndex[0]];
		const auto& vec1 = positions[face.posIndex[1]];
		const auto& vec2 = positions[face.posIndex[2]];

		auto normal = glm::normalize(glm::cross(vec1 - vec0, vec2 - vec0));
		normals.push_back(normal);
		face.normalIndex[0] = (normals.size() - 1);

		normal = glm::normalize(glm::cross(vec2 - vec1, vec0 - vec1));
		normals.push_back(normal);
		face.normalIndex[1] = (normals.size() - 1);

		normal = glm::normalize(glm::cross(vec0 - vec2, vec1 - vec2));
		normals.push_back(normal);
		face.normalIndex[2] = (normals.size() - 1);
	}
}