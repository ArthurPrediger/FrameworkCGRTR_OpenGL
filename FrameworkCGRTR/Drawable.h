#pragma once

#include <vector>
#include <memory>

class Drawable
{
public:
	Drawable(size_t numVertices);
	void Draw();
	void AddBindable(std::shared_ptr<class Bindable> bindable);
	void AddMaterial(std::shared_ptr<class Material> material);
private:
	std::vector<std::shared_ptr<Bindable>> onInitializationBindables;
	std::vector<std::shared_ptr<Bindable>> onDrawBindables;
	std::shared_ptr<Material> material;
private:
	size_t numVertices;
};