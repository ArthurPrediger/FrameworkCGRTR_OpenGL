#pragma once

#include "Bindable.h"
#include <vector>

class VAO : public Bindable
{
public:
	VAO();
	~VAO();
	virtual void Bind() override;
	GLuint GetVAO_ID() const
	{
		return vao;
	}
private:
	GLuint vao;
};
