#pragma once

#include "Material.h"
#include "SplitString.h"
#include "Texture2D.h"
#include <vector>
#include <memory>
#include <fstream>

class MTL_Loader
{
public:
	static std::vector<std::shared_ptr<Material>> LoadMtllib(const std::string& mtllib_path)
	{
		std::vector<std::shared_ptr<Material>> materials = {};

		std::ifstream file(mtllib_path);

		if (file.is_open())
		{
			std::vector<std::string> subStrs;
			std::string line;
			std::shared_ptr<Material> material = nullptr;

			while (!file.eof())
			{
				std::getline(file, line);

				subStrs = Split(line, ' ');

				if (subStrs[0] == "newmtl")
				{
					if (material)
					{
						materials.push_back(std::move(material));
						material.reset();
					}
					material = std::make_shared<Material>(mtllib_path, subStrs[1]);
				}
				if (subStrs[0] == "map_Kd" && subStrs[1] != "")
				{
					std::string texture_path = mtllib_path;
					auto offset = texture_path.find_last_of("/");
					texture_path.erase(offset + 1, texture_path.size() - offset - 1);
					for(size_t i = 1; i < subStrs.size(); i++) 
						texture_path.append(subStrs[1]);
					auto texture = Texture2D::Resolve(texture_path);
					material->textureMaps.push_back(std::move(texture));
				}
			}

			file.close();

			if (material)
			{
				materials.push_back(std::move(material));
			}

			return materials;
		}
		else
		{
			throw std::runtime_error("File path to load materials is incorrect or doesn't exist.");
		}

		return materials;
	}
};