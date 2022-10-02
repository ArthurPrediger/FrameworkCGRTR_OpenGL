#include "App.h"
#include "Scene_Loader.h"
#include "Sphere.h"
#include "ShootingSystem.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

App::App()
	:
	window(std::make_unique<Window>(960, 600, "FrameworkCGRTR's Window"))
{}

void App::Run()
{
	// inicia manipulador da extensão GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	// obtenção de versão suportada da OpenGL e renderizador
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "OpenGL (versao suportada) " << version << "\n";

	Camera camera{};
	std::vector<Mesh> meshes{};
	std::vector<GameObject> gameObjects{};
	Scene_Loader::LoadScene("Scene.txt", &camera, &meshes, &gameObjects);
	camera.Update(window.get(), 0.0f);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Timer timer{};

	ShootingSystem shooting_sys{&camera, &gameObjects};

	while (!glfwWindowShouldClose(window->GetWindow())) 
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, window->GetDimensions().width, window->GetDimensions().height);

		const float dt = timer.Tick();

		camera.Update(window.get(), dt);

		shooting_sys.Update(window.get(), dt);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();

		for (auto& gameObject : gameObjects)
		{
			gameObject.Draw(dt, view, projection);
		}

		glfwSwapBuffers(window->GetWindow());
	}
}
