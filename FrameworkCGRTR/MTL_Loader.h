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

			auto loadVertex = [&line, &subStrs]() {
				float x = 0, y = 0, z = 0;
				x = std::stof(subStrs[1]);
				y = std::stof(subStrs[2]);
				z = std::stof(subStrs[3]);

				return glm::vec4(x, y, z, 1.0f);
			};

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
				else if (subStrs[0] == "Kd")
				{
					Material::TemplatedMaterialProperty<glm::vec4> property{};
					property.name = "diffuse_color";
					property.property = loadVertex();
					material->properties.push_back(std::make_shared<Material::TemplatedMaterialProperty<glm::vec4>>(property));
				}
				else if (subStrs[0] == "Ka")
				{
					Material::TemplatedMaterialProperty<glm::vec4> property{};
					property.name = "ambient_color";
					property.property = loadVertex();
					material->properties.push_back(std::make_shared<Material::TemplatedMaterialProperty<glm::vec4>>(property));
				}
				else if (subStrs[0] == "Ks")
				{
					Material::TemplatedMaterialProperty<glm::vec4> property{};
					property.name = "specular_color";
					property.property = loadVertex();
					material->properties.push_back(std::make_shared<Material::TemplatedMaterialProperty<glm::vec4>>(property));
				}
				else if (subStrs[0] == "Ns")
				{
					Material::TemplatedMaterialProperty<float> property{};
					property.name = "specular_glow";
					property.property = std::stof(subStrs[1]);
					material->properties.push_back(std::make_shared<Material::TemplatedMaterialProperty<float>>(property));
				}
				else if (subStrs[0] == "map_Kd" && subStrs[1] != "")
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