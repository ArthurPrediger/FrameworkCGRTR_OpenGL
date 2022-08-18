#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Drawable.h"
#include "Bindable.h"
#include "ShaderProgram.h"

Drawable::Drawable(const std::vector<float>& vertices)
	:
	vertices(vertices)
{}

void Drawable::Draw()
{
	for (auto& bindable : onDrawBindables)
	{
		bindable->Bind();
	}
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Drawable::AddBindable(std::shared_ptr<Bindable> bindable)
{
	if (bindable->GetType() == "ShaderProgram" || bindable->GetType() == "VAO")
	{
		onDrawBindables.push_back(bindable);
		if (bindable->GetType() == "ShaderProgram")
		{
			std::reinterpret_pointer_cast<ShaderProgram>(bindable)->Setup();
		}
	}
	else
	{
		onInitializationBindables.push_back(bindable);
		bindable->Bind();
	}
}
