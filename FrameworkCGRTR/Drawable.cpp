#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Drawable.h"
#include "Bindable.h"
#include "ShaderProgram.h"
#include "BindableSet.h"
#include "Mesh.h"
#include "Material.h"

Drawable::Drawable(size_t numVertices)
	:
	numVertices(numVertices),
	material(nullptr)
{}

void Drawable::Draw()
{
	for (auto& bindable : onDrawBindables)
	{
		bindable->Bind();
	}
	if (material)
	{
		material->BindTextureMaps();
	}
	glDrawArrays(GL_TRIANGLES, 0, GLsizei(numVertices));
	glBindVertexArray(0);
	glUseProgram(0);
}

void Drawable::AddBindable(std::shared_ptr<Bindable> bindable)
{
	if (bindable->GetBindType() == Bindable::BindType::OnDraw)
	{
		onDrawBindables.push_back(bindable);
	}
	else
	{
		onInitializationBindables.push_back(bindable);
	}
}

void Drawable::AddMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}
