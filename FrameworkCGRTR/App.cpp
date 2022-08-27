#include "App.h"
#include "TestCube.h"
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
	// inicia manipulador da extens�o GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	// obten��o de vers�o suportada da OpenGL e renderizador
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "OpenGL (versao suportada) " << version << "\n";

	TestCube cube;
	TestCube cube1;

	glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window->GetWindow())) 
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, window->GetDimensions().width, window->GetDimensions().height);

		const float dt = timer.Tick();

		cube.angle += glm::pi<float>() * dt / 5;

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(50.0f), (float)window->GetDimensions().width / (float)window->GetDimensions().height, 0.1f, 100.0f);

		glm::mat4 view = glm::identity<glm::mat4>();
		view = glm::translate(view, { 1.0f, 0.0f, -3.0f });
		view = glm::rotate(view, cube.angle, { 1.0f, 1.0f, 0.0f });

		*cube.transform = projection * view;

		cube.Draw(dt);

		cube1.angle += glm::pi<float>() * dt / 5;

		view = glm::identity<glm::mat4>();
		view = glm::translate(view, { -1.0f, 0.0f, -3.0f });
		view = glm::rotate(view, cube1.angle, { 1.0f, 1.0f, 0.0f });

		*cube1.transform = projection * view;

		cube1.Draw(dt);

		glfwSwapBuffers(window->GetWindow());
	}
}
