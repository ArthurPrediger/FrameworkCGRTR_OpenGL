#pragma once

#include "Bindable.h"
#include "Mesh.h"
#include <vector>
#include <memory>

class VBO : public Bindable
{
	friend class VAO;
public:
	VBO(const std::vector<Mesh::Vertex>& vertices, const std::string& name);
	VBO() = delete;
	~VBO();
	static std::shared_ptr<VBO> Resolve(const std::vector<Mesh::Vertex>& vertices, const std::string& name);
	static std::string GetUniqueID(const std::vector<Mesh::Vertex>& vertices, const std::string& name);
	GLuint GetVBO_ID() const
	{
		return vbo;
	}
	const std::string& GetName() const override
	{
		return name;
	}
private:
	void Bind() override;
private:
	std::string name;
	std::vector<Mesh::Vertex> vertices;
	GLuint vao;
	GLuint vbo;
};
