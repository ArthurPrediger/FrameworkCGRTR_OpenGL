#include "VBO.h"
#include "VAO.h"
#include <typeinfo>

VBO::VBO(VAO& vao, const std::vector<float>& vertices)
	:
	Bindable("VBO"),
	code("vbo" + std::to_string(vertices.size())),
	vao(vao),
	vertices(vertices),
	vbo(NULL)
{
	vao.VBOAdded(code);
}

VBO::~VBO()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1, &vbo);
}

void VBO::Bind()
{
	glBindVertexArray(vao.GetVAO_ID());

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
