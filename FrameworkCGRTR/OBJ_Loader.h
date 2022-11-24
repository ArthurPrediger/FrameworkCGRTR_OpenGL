#pragma once

#include <string>

class OBJ_Loader
{
public:
	static class Mesh LoadMesh(const std::string& mesh_file_path);
};