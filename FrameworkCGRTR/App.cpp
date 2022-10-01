#include "App.h"
#include "OBJ_Loader.h"
#include "GameObject.h"
#include "Sphere.h"
#include "ShootingSystem.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

App::App()
	:
	window(std::make_unique<Window>(960, 540, "FrameworkCGRTR's Window")),
	camera(Camera())
{
	double xPos = 0.0f, yPos = 0.0f;
	glfwGetCursorPos(window->GetWindow(), &xPos, &yPos);
	camera.prevMousePos.first = xPos;
	camera.prevMousePos.second = yPos;
}

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

	Mesh car = OBJ_Loader::LoadMesh("../3dModels/car/Car.obj");
	Mesh wheel = OBJ_Loader::LoadMesh("../3dModels/car/Wheel.obj");
	Mesh dragon = OBJ_Loader::LoadMesh("../3dModels/dragon/alduin.obj");
	Mesh katarina = OBJ_Loader::LoadMesh("../3dModels/katarina/katarina.obj");
	Mesh sphere = Sphere::GetMesh(1.0f);
	//Mesh trout = OBJ_Loader::LoadMesh("../3dModels/trout/trout.obj");

	std::vector<GameObject> gameObjects = {
		//{&trout, { 0.0f, 0.0f, -10.0f }, "TextureVS.txt", "TextureFS.txt"},
		{&car, { 0.0f, 0.0f, -10.0f }, "TextureVS.txt", "TextureFS.txt", { -glm::half_pi<float>(), 0.0f, 0.0f } },
		{&wheel, { 0.0f, 0.0f, -10.0f }, "TextureVS.txt", "TextureFS.txt", { -glm::half_pi<float>(), 0.0f, 0.0f } },
		{&dragon, { -10.0f, 0.0f, -10.0f }, "TextureVS.txt", "TextureFS.txt", { 0.0f, -glm::half_pi<float>(), 0.0f }, 0.01f },
		{&katarina, { 3.0f, 0.0f, -10.0f }, "TextureVS.txt", "TextureFS.txt", { 0.0f, 0.0f, 0.0f }, 0.25f},
		{&sphere, { 0.0f, -3.0f, -10.0f }, "SimpleVertexShader.txt", "SimpleFragmentShader.txt" } 
	};

	gameObjects[3].is_destructible = true;
	gameObjects[4].is_destructible = true;

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
