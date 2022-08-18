#pragma once

#include "Bindable.h"
#include <vector>

class VAO : public Bindable
{
public:
	VAO();
	~VAO();
	virtual void Bind() override;
	virtual const std::string& GetCode() const override
	{
		return code;
	}
	void VBOAdded(const std::string& vbo_code)
	{
		code.append(vbo_code);
	}
	GLuint GetVAO_ID() const
	{
		return vao;
	}
private:
	std::string code;
	GLuint vao;
};
