#pragma once

#include "Bindable.h"
#include <vector>

class VBO : public Bindable
{
public:
	VBO(GLuint vao, const std::vector<float>& vertices);
	~VBO();
	virtual void Bind() override;
	GLuint GetVBO_ID() const
	{
		return vbo;
	}
private:
	GLuint vbo;
};
