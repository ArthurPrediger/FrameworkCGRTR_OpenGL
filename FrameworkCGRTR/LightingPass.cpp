#include "LightingPass.h"
#include "Bindable.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "UniformLocation.h"
#include "Camera.h"
#include "GameObject.h"
#include "Sphere.h"

LightingPass::LightingPass(std::vector<GameObject>& game_objects, Camera* camera)
	:
	game_objects(game_objects),
	camera(camera),
	camera_position(std::make_shared<glm::vec4>(camera->GetPosition(), 1.0f)),
	point_light_position(std::make_shared<glm::vec4>(glm::vec4{ 0.0f, 5.0f, -2.0f, 0.0f }))
{
	std::shared_ptr<VertexShader> vs = VertexShader::Resolve("LightingVS.txt");
	onInitializationBindables.push_back(vs);

	std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("LightingFogFS.txt");
	onInitializationBindables.push_back(fs);

	std::shared_ptr<ShaderProgram> sp = ShaderProgram::Resolve(vs, fs);
	onDrawBindables.push_back(sp);

	std::shared_ptr<UniformLocation<glm::vec4>> unifLoc_light_pos = UniformLocation<glm::vec4>::Resolve(sp, "light_position", point_light_position);
	sp->AddUniformLocationBindable(unifLoc_light_pos);

	std::shared_ptr<UniformLocation<glm::vec4>> unifLoc_camera_pos = UniformLocation<glm::vec4>::Resolve(sp, "camera_position", camera_position);
	sp->AddUniformLocationBindable(unifLoc_camera_pos);

	for (auto& game_object : game_objects)
	{
		game_object.BindShaderProgram(sp);
	}

	light_mesh = std::make_unique<Mesh>(Sphere::GetMesh());

	std::shared_ptr<VertexShader> vs_light = VertexShader::Resolve("SimpleVertexShader.txt");
	light_mesh->QueryGroup(0)->AddBindable(vs_light);

	std::shared_ptr<FragmentShader> fs_light = FragmentShader::Resolve("SimpleFragmentShader.txt");
	light_mesh->QueryGroup(0)->AddBindable(fs_light);

	light_object = std::make_unique<GameObject>(light_mesh.get(), glm::vec3(*point_light_position), glm::vec3(0.0f), 0.4f);
	std::shared_ptr<ShaderProgram> sp_light = ShaderProgram::Resolve(vs_light, fs_light);
	light_object->BindShaderProgram(sp_light);
};

void LightingPass::Render(float dt)
{
	for (auto& bindable : onDrawBindables)
	{
		bindable->Bind();
	}

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = camera->GetProjectionMatrix();
	*camera_position = glm::vec4{ camera->GetPosition(), 1.0f };

	for (auto& gameObject : game_objects)
	{
		gameObject.Draw(dt, view, projection);
	}

	light_object->Draw(dt, view, projection);
};