#include "Scene_Loader.h"
#include "OBJ_Loader.h"
#include "GameObject.h"
#include "Camera.h"
#include "SplitString.h"
#include "Mesh.h"

#include <glm/glm.hpp> 

#include <fstream>
#include <stdexcept>
#include <ranges>

void Scene_Loader::LoadScene(const std::string& scene_path, Camera* camera, std::vector<Mesh>* meshes, std::vector<GameObject>* game_objects)
{
	std::ifstream file(scene_path);

	if (file.is_open())
	{
		std::vector<std::string> subStrs;
		std::string line;
		std::vector<std::pair<std::string, size_t>> mesh_name_linker{};

		while (!file.eof())
		{
			std::getline(file, line);

			subStrs = Split(line, ' ');

			auto str_to_vec3 = [](std::vector<std::string>::iterator first) {
				glm::vec3 vector(0.0f);
				vector.x = std::stof(*(first++));
				vector.y = std::stof(*(first++));
				vector.z = std::stof(*(first));
				return vector;
			};

			if (subStrs[0] == "m")
			{
				meshes->push_back(OBJ_Loader::LoadMesh(subStrs[2]));
				mesh_name_linker.push_back({ subStrs[1], meshes->size() - 1 });
			}
			if (subStrs[0] == "o")
			{
				Mesh* mesh = &(*meshes)[std::ranges::find_if(mesh_name_linker, [&subStrs](const std::pair<std::string, size_t>& pair)
					{ return pair.first == subStrs[1]; })->second];
				const glm::vec3 world_pos = str_to_vec3(subStrs.begin() + 2);
				const glm::vec3 world_rot = str_to_vec3(subStrs.begin() + 5);
				const float scale = std::stof(subStrs[8]);

				const int description = std::stoi(subStrs[9]);
				game_objects->emplace_back(GameObject{ mesh, world_pos, world_rot, scale, description });
			}
			if (subStrs[0] == "c")
			{
				const glm::vec3 world_pos = str_to_vec3(subStrs.begin() + 1);
				const glm::vec3 forward = str_to_vec3(subStrs.begin() + 4);
				const glm::vec3 up = str_to_vec3(subStrs.begin() + 7);

				camera->position = world_pos;
				camera->forward = forward;
				camera->up = up;
			}
		}

		file.close();
	}
	else
	{
		throw std::runtime_error("File path to load materials is incorrect or doesn't exist.");
	}
}
