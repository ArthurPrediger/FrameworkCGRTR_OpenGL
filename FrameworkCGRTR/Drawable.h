#pragma once

#include <vector>
#include <memory>

class Drawable
{
public:
	Drawable(const std::vector<float>& vertices);
	void Draw();
	void AddBindable(std::shared_ptr<class Bindable> bindable);
private:
	std::vector<std::shared_ptr<Bindable>> onInitializationBindables;
	std::vector<std::shared_ptr<Bindable>> onDrawBindables;
protected:
	std::vector<float> vertices;
};