#pragma once

#include "Drawable.h"
#include <string>

class Group : public Drawable
{
public:
	struct Face
	{
		size_t posIndex[3];
		size_t normalIndex[3];
		size_t textureIndex[3];
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