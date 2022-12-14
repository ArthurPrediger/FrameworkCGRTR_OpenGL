#include "Mesh.h"
#include "VAO.h"
#include "VBO.h"
#include <assert.h>

Mesh::Mesh(const Vertices& vertices)
	:
	vertsPos(vertices.vertsPos),
	vertsNormals(vertices.vertsNormals),
	vertsTexts(vertices.vertsTexts)
{}

void Mesh::AddGroup(const std::string& groupName, const std::vector<Group::Face>& faces)
{
	groups.emplace_back(Group{ groupName, faces });

	AddBindablesToGroup(groups.size() - 1);
}

void Mesh::AddGroup(const Group& group)
{
	groups.push_back(group);

	AddBindablesToGroup(groups.size() - 1);
}

Group* Mesh::QueryGroup(size_t groupIndex)
{
	if (groupIndex < groups.size())
	{
		return &groups[groupIndex];
	}

	return nullptr;
}

Group* Mesh::QueryGroup(const std::string& name)
{
	for (Group& group : groups)
	{
		if (group.GetName() == name)
		{
			return &group;
		}
	}

	return nullptr;
}

std::vector<Mesh::Vertex> Mesh::GetVerticesFromGroup(size_t groupIndex) const
{
	assert(groupIndex < groups.size());
	std::vector<Vertex> groupVertices;

	const auto& faces = groups[groupIndex].GetFaces();

	for (const Group::Face& face : faces)
	{
		for (int i = 0; i < 3; i++)
		{
			groupVertices.push_back({ 
				vertsPos[face.posIndex[i]],
				vertsNormals[face.normalIndex[i]],
				vertsTexts[face.textureIndex[i]] });
		}
	}

	return groupVertices;
}

std::vector<Mesh::Vertex> Mesh::GetVerticesFromGroup(const std::string& groupName) const
{
	size_t i = 0;
	while (i < groups.size() && groupName != groups[i].GetName())
	{
		i++;
	}

	return GetVerticesFromGroup(i);
}

void Mesh::Draw()
{
	for (Group& group : groups)
	{
		group.Draw();
	}
}

void Mesh::AddBindablesToGroup(size_t groupIndex)
{
	Group& group = groups[groupIndex];

	std::shared_ptr<VBO> vbo = VBO::Resolve(std::move(GetVerticesFromGroup(groupIndex)), group.GetName());
	group.AddBindable(vbo);

	std::shared_ptr<VAO> vao = VAO::Resolve({ vbo });
	group.AddBindable(vao);
}
