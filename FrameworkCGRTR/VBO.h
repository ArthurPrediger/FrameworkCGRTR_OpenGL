#pragma once

#include "Bindable.h"
#include "Mesh.h"
#include <vector>
#include <memory>

class VBO : public Bindable
{
	friend class VAO;
public:
	VBO() = delete;
	~VBO();
	static std::shared_ptr<VBO> Resolve(const std::vector<Mesh::Vertex>& vertices, const std::string& name);
	GLuint GetVBO_ID() const
	{
		return vbo;
	}
private:
	VBO(const std::vector<Mesh::Vertex>& vertices, const std::string& name);
	void Bind() override;
private:
	std::vector<Mesh::Vertex> vertices;
	GLuint vao;
	GLuint vbo;
};
