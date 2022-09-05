#include "App.h"
#include "OBJ_Loader.h"
#include "GameObject.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

App::App()
	:
	window(std::make_unique<Window>(640, 480, "FrameworkCGRTR's Window")),
	timer(Timer()),
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

	//Mesh trout = OBJ_Loader::LoadMesh("../3dModels/trout/trout.obj");
	//Mesh pyramid = OBJ_Loader::LoadMesh("../3dModels/pyramid/pyramid.obj");
	Mesh dragon = OBJ_Loader::LoadMesh("../3dModels/dragon/dragon.obj");

	GameObject gameObject{&dragon};

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window->GetWindow())) 
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, window->GetDimensions().width, window->GetDimensions().height);

		const float dt = timer.Tick();

		camera.Update(window.get(), dt);

		glm::mat4 world = glm::identity<glm::mat4>();
		world = glm::translate(world, { 0.0f, 0.0f, -3.0f });
		world = glm::rotate(world, glm::pi<float>() / 2.0f , { -1.0f, 0.0f, 0.0f });

		gameObject.SetTransform(camera.GetViewProjectionMatrix() * world);

		gameObject.Draw(dt);

		glfwSwapBuffers(window->GetWindow());
	}
}
