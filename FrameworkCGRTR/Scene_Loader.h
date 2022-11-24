#pragma once

#include <string>
#include <vector>

class Scene_Loader
{
public:
	static void LoadScene(const std::string& scene_path, class Camera* camera, std::vector<class Mesh>* meshes,
		std::vector<class GameObject>* game_objects);
};