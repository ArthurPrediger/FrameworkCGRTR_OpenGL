#include "App.h"
#include "OBJ_Loader.h"
#include "TestModel.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

App::App()
	:
	window(std::make_unique<Window>(640, 480, "FrameworkCGRTR's Window")),
	timer(Timer())
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

	Mesh trout = OBJ_Loader::LoadMesh("../3dModels/trout/trout.obj");

	TestModel model{&trout};

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

		model.angle += glm::pi<float>() * dt / 5;

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(50.0f), (float)window->GetDimensions().width / (float)window->GetDimensions().height, 0.1f, 100.0f);

		glm::mat4 view = glm::identity<glm::mat4>();
		view = glm::translate(view, { -1.0f, 0.0f, -10.0f });
		view = glm::rotate(view, model.angle, { 0.0f, 1.0f, 0.0f });

		*model.transform = projection * view;

		model.Draw(dt);

		glfwSwapBuffers(window->GetWindow());
	}
}
