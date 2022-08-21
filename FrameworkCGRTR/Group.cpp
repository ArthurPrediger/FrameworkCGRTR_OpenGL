#include "Group.h"

Group::Group(const std::string& name, const std::vector<Face>& faces)
	:
	name(name),
	faces(faces), 
	Drawable(faces.size() * size_t(3))
{
}
