#include "App.h"
#include <iostream>
#include "TestTriangle.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

App::App()
	:
	window(std::make_unique<Window>(640, 480, "FrameworkCGRTR's Window"))
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

	TestTriangle triangle;

	while (!glfwWindowShouldClose(window->GetWindow())) 
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		triangle.Draw();

		glfwSwapBuffers(window->GetWindow());
	}
}
