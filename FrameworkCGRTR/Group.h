#pragma once

#include "Drawable.h"
#include <string>
#include <array>

class Group : public Drawable
{
	friend class OBJ_Loader;
public:
	struct Face
	{
		std::array<size_t, 3> posIndex;
		std::array<size_t, 3> textureIndex;
		std::array<size_t, 3> normalIndex;
	};
	Group(const std::string& name, const std::vector<Face>& faces);
	const std::string& GetName() const
	{
		return name;
	}
	const std::vector<Face>& GetFaces() const
	{
		return faces;
	}
private:
	std::string name;
	std::vector<Face> faces;
};