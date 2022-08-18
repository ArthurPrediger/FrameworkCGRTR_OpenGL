#include "VAO.h"

VAO::VAO()
	:
	Bindable("VAO"),
	code("vao")
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vao);
}

void VAO::Bind()
{
	glBindVertexArray(vao);
}
