#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

class LightingPass
{
public:
	LightingPass(std::vector<class GameObject>& game_objects, class Camera* camera);
	void Render(float dt);
private:
	std::vector<std::shared_ptr<class Bindable>> onInitializationBindables;
	std::vector<std::shared_ptr<Bindable>> onDrawBindables;
	std::vector<GameObject>& game_objects;
	Camera* camera;
	std::shared_ptr<glm::vec4> point_light_position;
	std::unique_ptr<class Mesh> light_mesh;
	std::unique_ptr<GameObject> light_object;
};