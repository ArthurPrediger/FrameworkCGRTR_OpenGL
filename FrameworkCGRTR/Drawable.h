#pragma once

#include "Bindable.h"

#include <vector>
#include <memory>
#include <string>

class Drawable
{
public:
	Drawable(size_t numVertices);
	void Draw();
	void AddBindable(std::shared_ptr<Bindable> bindable);
	void AddMaterial(std::shared_ptr<class Material> material);
	void EraseBindableByType(const std::string& bindable_type, const Bindable::BindType& bind_type);
private:
	std::vector<std::shared_ptr<Bindable>> onInitializationBindables;
	std::vector<std::shared_ptr<Bindable>> onDrawBindables;
	std::shared_ptr<Material> material;
private:
	size_t numVertices;
};