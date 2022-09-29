#include "VBO.h"
#include "VAO.h"
#include "BindableSet.h"

VBO::VBO(const std::vector<Mesh::Vertex>& vertices, const std::string& name)
	:
	Bindable("VBO", BindType::OnInitialization),
	name(name + "_" + std::to_string(vertices.size())),
	vertices(vertices),
	vao(NULL),
	vbo(NULL)
{}

VBO::~VBO()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1, &vbo);
}

std::shared_ptr<VBO> VBO::Resolve(const std::vector<Mesh::Vertex>& vertices, const std::string& name)
{
	auto vbo = BindableSet::Resolve<VBO>(vertices, name);
	return vbo.second;
}

std::string VBO::GetUniqueID(const std::vector<Mesh::Vertex>& vertices, const std::string& name)
{
	return "VBO_" + name + "_" + std::to_string(vertices.size());
};

void VBO::Bind()
{
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices.front(), GL_STATIC_DRAW);

	// Posições:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normais:										
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texturas:									
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}
