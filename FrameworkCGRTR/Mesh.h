#pragma once

#include "Group.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

class Mesh
{
public: 
	struct Vertices
	{
		std::vector<glm::vec3> vertsPos;
		std::vector<glm::vec3> vertsNormals;
		std::vector<glm::vec2> vertsTexts;
	};
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texture;
	};
public:
	Mesh(const Vertices& vertices);
	void AddGroup(const std::string& groupName, const std::vector<Group::Face>& faces);
	void AddGroup(const Group& group);
	Group* QueryGroup(size_t groupIndex);
	Group* QueryGroup(const std::string& groupName);
	Vertices GetVertices() const
	{
		return {vertsPos, vertsNormals, vertsTexts};
	}
	std::vector<Vertex> GetVerticesFromGroup(size_t groupIndex) const;
	std::vector<Vertex> GetVerticesFromGroup(const std::string& groupName) const;
	void Draw();
private:
	void AddBindablesToGroup(size_t groupIndex);
private:
	std::vector<glm::vec3> vertsPos;
	std::vector<glm::vec3> vertsNormals;
	std::vector<glm::vec2> vertsTexts;
	std::vector<Group> groups;
};