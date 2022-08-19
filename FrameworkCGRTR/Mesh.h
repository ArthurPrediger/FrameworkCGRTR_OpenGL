#pragma once

#include "Drawable.h"

class Mesh : public Drawable
{
public:
	Mesh(const std::vector<float>& vertices);
private:
	glm::mat4x4 transform;
};