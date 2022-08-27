#include "App.h"
#include "TestDiamond.h"
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

	TestDiamond diamond;

	glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window->GetWindow())) 
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, window->GetDimensions().width, window->GetDimensions().height);

		diamond.Draw(timer.Tick());

		glfwSwapBuffers(window->GetWindow());
	}
}
