#include "LightingPass.h"
#include "Bindable.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "UniformLocation.h"
#include "Camera.h"
#include "GameObject.h"

LightingPass::LightingPass(std::vector<GameObject>& game_objects, Camera* camera)
	:
	game_objects(game_objects),
	camera(camera),
	point_light_position(std::make_shared<glm::vec4>(glm::vec4{ 0.0f, 10.0f, 5.0f, 0.0f }))
{
	std::shared_ptr<VertexShader> vs = VertexShader::Resolve("LightingVS.txt");
	onInitializationBindables.push_back(vs);

	std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("LightingFS.txt");
	onInitializationBindables.push_back(fs);

	std::shared_ptr<ShaderProgram> sp = ShaderProgram::Resolve(vs, fs);
	onDrawBindables.push_back(sp);

	std::shared_ptr<UniformLocation<glm::vec4>> unifLoc_light_pos = UniformLocation<glm::vec4>::Resolve(sp, "light_position", point_light_position);
	sp->AddUniformLocationBindable(unifLoc_light_pos);

	for (auto& game_object : game_objects)
	{
		game_object.BindShaderProgram(sp);
	}
};

void LightingPass::Render(float dt)
{
	for (auto& bindable : onDrawBindables)
	{
		bindable->Bind();
	}

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = camera->GetProjectionMatrix();

	for (auto& gameObject : game_objects)
	{
		gameObject.Draw(dt, view, projection);
	}
};