#include "VBO.h"
#include "VAO.h"
#include "BindableSet.h"

VBO::VBO(const std::vector<float>& vertices, const std::string& name)
	:
	Bindable("VBO", "VBO_" + name, BindType::OnInitilization),
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

std::shared_ptr<VBO> VBO::Resolve(const std::vector<float>& vertices, const std::string& name)
{
	auto vbo = std::shared_ptr<VBO>(new VBO(vertices, name));
	BindableSet::Resolve(vbo);
	return vbo;
}

void VBO::Bind()
{
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices.front(), GL_STATIC_DRAW);

	// Posições:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Cores:
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}
