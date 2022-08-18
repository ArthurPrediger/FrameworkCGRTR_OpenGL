#pragma once

#include "Bindable.h"
#include <vector>

class VBO : public Bindable
{
public:
	VBO(class VAO& vao, const std::vector<float>& vertices);
	~VBO();
	virtual void Bind() override;
	virtual const std::string& GetCode() const override
	{
		return code;
	}
	GLuint GetVBO_ID() const
	{
		return vbo;
	}
private:
	std::string code;
	VAO& vao;
	const std::vector<float>& vertices;
	GLuint vbo;
};
