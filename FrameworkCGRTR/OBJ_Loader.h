#pragma once

#include "Mesh.h"
#include "MTL_Loader.h"
#include "CalculateNormals.h"
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

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
			std::string curGroupName = mesh_file_path;
			std::vector<Group::Face> curGroupFaces;
			std::vector<std::string> mtllib_paths;
			std::vector<std::string> groupsMaterials;
			std::string curMaterialName = "";

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
					vertices.vertsNormals.push_back(loadVertex(3));;
				}
				else if (subStrs[0] == "g")
				{
					if (curGroupFaces.size() > 0)
					{
						groups.emplace_back(Group{ curGroupName, curGroupFaces });
						groupsMaterials.push_back(curMaterialName);
						curMaterialName = "";
					}

					if (subStrs.size() > 1)
					{
						curGroupName.clear();
						size_t i;
						for (i = 1; i < subStrs.size(); i++)
						{
							curGroupName.append(subStrs[i] + "_");
						}
						curGroupName.erase(curGroupName.size() - 1, 1);
					}
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

						curVertIndices = { 0, 0, 0 };
						curVertIndices[0] = static_cast<size_t>(std::stoi(faceVertexIndices[0])) - 1;
						if(vertices.vertsTexts.size() > 0)
							curVertIndices[1] = static_cast<size_t>(std::stoi(faceVertexIndices[1])) - 1;
						if(vertices.vertsNormals.size() > 0)
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
				else if (subStrs[0] == "mtllib")
				{
					std::string path_to_mtllib = mesh_file_path;
					auto offset = path_to_mtllib.find_last_of("/");
					path_to_mtllib.erase(offset + 1, path_to_mtllib.size() - offset - 1);
					mtllib_paths.push_back(path_to_mtllib + subStrs[1]);
				}
				else if (subStrs[0] == "usemtl")
				{
					curMaterialName = subStrs[1];
				}
			}

			file.close();

			if (curGroupFaces.size() > 0)
			{
				groups.emplace_back(Group{ curGroupName, curGroupFaces });
				groupsMaterials.push_back(curMaterialName);
			}

			if (vertices.vertsTexts.size() == 0)
				vertices.vertsTexts = { { 0.0f , 0.0f } };
			if (vertices.vertsNormals.size() == 0)
			{
				//vertices.vertsNormals = { { 0.0f , 0.0f, 0.0f } };

				for (auto& group : groups)
				{
					CalculateNormals(vertices.vertsPos, group.faces, vertices.vertsNormals);
				}
			}				

			Mesh mesh{ vertices };

			if (mtllib_paths.size() > 0)
			{
				auto materials = MTL_Loader::LoadMtllib(mtllib_paths[0]);
				for (size_t i = 0; i < groups.size(); i++)
				{
					if (groupsMaterials[i] != "")
					{
						std::shared_ptr<Material> material = *std::find_if(materials.begin(), materials.end(),
							[i, &groupsMaterials](std::shared_ptr<Material> material) { return material->GetName() == groupsMaterials[i]; });
						groups[i].AddMaterial(material);
					}
				}
			}

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