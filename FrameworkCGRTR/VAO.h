#pragma once

#include "Bindable.h"
#include <vector>
#include <memory>

class VAO : public Bindable
{
public:
	~VAO();
	void Bind() override;
	GLuint GetVAO_ID() const
	{
		return vao;
	}
	static std::shared_ptr<VAO> Resolve(std::vector<std::shared_ptr<class VBO>> VBOs);
private:
	VAO(std::vector<std::shared_ptr<VBO>> VBOs);
	void Generate();
private:
	GLuint vao;
};
