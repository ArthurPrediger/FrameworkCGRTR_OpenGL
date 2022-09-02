#pragma once

#include "Mesh.h"
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <stdexcept>

std::vector<std::string> Split(const std::string& str, char delimeter)
{
	std::vector<std::string> subStrings{};
	std::string subStr{};
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != delimeter)
		{
			subStr.append(1, str[i]);
		}
		else if (str[i] == delimeter && subStr.size() > 0)
		{
			subStrings.push_back(subStr);
			subStr.clear();
		}
	}
	subStrings.push_back(subStr);
	subStr.clear();

	return subStrings;
}

class OBJ_Loader
{
public:
	static Mesh LoadMesh(const std::string& mesh_file_path)
	{
		std::ifstream file(mesh_file_path);

		if (file.is_open())
		{
			Mesh::Vertices vertices;

			std::vector<Group> groups;
			std::string curGroupName;
			std::vector<Group::Face> curGroupFaces;

			std::vector<std::string> subStrs;
			std::string line;

			auto loadVertex = [&line, &subStrs](unsigned int nDimensions) {
				float x = 0, y = 0, z = 0;
				switch (nDimensions)
				{
				case 2:
					x = std::stof(subStrs[1]);
					y = std::stof(subStrs[2]);
					break;
				case 3:
					x = std::stof(subStrs[1]);
					y = std::stof(subStrs[2]);
					z = std::stof(subStrs[3]);
					break;
				default:
					break;
				}

				return glm::vec3(x, y, z);
			};
			while (!file.eof())
			{
				std::getline(file, line);

				subStrs = Split(line, ' ');

				if (subStrs[0] == "v")
				{
					vertices.vertsPos.push_back(loadVertex(3));
				}
				else if (subStrs[0] == "vt")
				{
					vertices.vertsTexts.push_back(loadVertex(2));
				}
				else if (subStrs[0] == "vn")
				{
					vertices.vertsNormals.push_back(loadVertex(3));
				}
				else if (subStrs[0] == "g")
				{
					if (curGroupFaces.size() > 0)
					{
						groups.emplace_back(Group{ curGroupName, curGroupFaces });
					}

					curGroupName = subStrs[2];
					curGroupFaces.clear();
				}
				else if (subStrs[0] == "f")
				{
					const size_t nVertices = subStrs.size() - 1;
					assert(nVertices >= 3);
					std::vector<std::array<size_t, 3>> vertIndices;
					std::array<size_t, 3> curVertIndices{};

					for (size_t i = 0; i < nVertices; i++)
					{
						auto faceVertexIndices = Split(subStrs[i + 1], '/');

						curVertIndices[0] = static_cast<size_t>(std::stoi(faceVertexIndices[0])) - 1;
						curVertIndices[1] = static_cast<size_t>(std::stoi(faceVertexIndices[1])) - 1;
						curVertIndices[2] = static_cast<size_t>(std::stoi(faceVertexIndices[2])) - 1;

						vertIndices.push_back(curVertIndices);
					}

					switch (nVertices)
					{
					case 3:
						curGroupFaces.emplace_back(Group::Face{ 
							{vertIndices[0][0], vertIndices[1][0], vertIndices[2][0]}, 
							{vertIndices[0][1], vertIndices[1][1], vertIndices[2][1]},
							{vertIndices[0][2], vertIndices[1][2], vertIndices[2][2]} });
						break;
					case 4:
						curGroupFaces.emplace_back(Group::Face{
							{vertIndices[0][0], vertIndices[1][0], vertIndices[2][0]},
							{vertIndices[0][1], vertIndices[1][1], vertIndices[2][1]},
							{vertIndices[0][2], vertIndices[1][2], vertIndices[2][2]} });
						curGroupFaces.emplace_back(Group::Face{
							{vertIndices[2][0], vertIndices[3][0], vertIndices[0][0]},
							{vertIndices[2][1], vertIndices[3][1], vertIndices[0][1]},
							{vertIndices[2][2], vertIndices[3][2], vertIndices[0][2]} });
						break;
					default:
						throw std::runtime_error("Trying to load model with unsupported number of vertices per face.");
						break;
					}
				}
			}

			file.close();

			if (curGroupFaces.size() > 0)
			{
				groups.emplace_back(Group{ curGroupName, curGroupFaces });
			}

			Mesh mesh{ vertices };

			for (auto& group : groups)
			{
				mesh.AddGroup(group);
			}

			return mesh;
		}
		else
		{
			throw std::runtime_error("File path to load mesh is incorrect or doesn't exist.");
		}

		return Mesh{{}};
	}
};