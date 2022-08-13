#include "VAO.h"

VAO::VAO()
	:
	Bindable("VAO")
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
