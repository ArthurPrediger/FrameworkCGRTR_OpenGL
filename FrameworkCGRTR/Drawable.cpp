#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Drawable.h"
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
		material->BindProperties();
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

		if (bindable->GetType() == "ShaderProgram" && material)
			material->SetPropertiesBindTarget(std::static_pointer_cast<ShaderProgram>(GetBindableByType("ShaderProgram", Bindable::BindType::OnDraw)));
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

std::shared_ptr<Bindable> Drawable::GetBindableByType(const std::string& bindable_type, const Bindable::BindType& bind_type)
{
	if (bind_type == Bindable::BindType::OnDraw)
	{
		for (auto& bindable : onDrawBindables)
		{
			if (bindable->GetType() == bindable_type)
				return bindable;
		}
	}
	if (bind_type == Bindable::BindType::OnInitialization)
	{
		for (auto& bindable : onInitializationBindables)
		{
			if (bindable->GetType() == bindable_type)
				return bindable;
		}
	}

	return nullptr;
}

void Drawable::EraseBindableByType(const std::string& bindable_type, const Bindable::BindType& bind_type)
{
	if (bind_type == Bindable::BindType::OnDraw)
	{
		for (size_t i = 0; i < onDrawBindables.size();)
		{
			if (onDrawBindables[i]->GetType() == bindable_type)
			{
				onDrawBindables.erase(onDrawBindables.begin() + i);
			}
			else i++;
		}
	}
	if (bind_type == Bindable::BindType::OnInitialization)
	{
		for (size_t i = 0; i < onInitializationBindables.size();)
		{
			if (onInitializationBindables[i]->GetType() == bindable_type)
			{
				onInitializationBindables.erase(onInitializationBindables.begin() + i);
			}
			else i++;
		}
	}
}
