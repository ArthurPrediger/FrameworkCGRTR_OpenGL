#pragma once

#include "Bindable.h"
#include <vector>
#include <memory>

class VBO : public Bindable
{
	friend class VAO;
public:
	VBO() = delete;
	~VBO();
	static std::shared_ptr<VBO> Resolve(const std::vector<float>& vertices, const std::string& name);
	GLuint GetVBO_ID() const
	{
		return vbo;
	}
private:
	VBO(const std::vector<float>& vertices, const std::string& name);
	void Bind() override;
private:
	const std::vector<float>& vertices;
	GLuint vao;
	GLuint vbo;
};
