//
// Window.cpp
// The window class handles the creation of a open gl window
// Created by David Harabagiu on 21.12.2017
//

#include <iostream>
#include "Window.h"
#include "Input.h"

Window::Window(int Width, int Height, char* Title)
{
	if (!glfwInit())
	{
		std::cerr << "ERROR: could not start GLFW3\n";
		return;
	}

	glWindow = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	if (!glWindow)
	{
		std::cerr << "ERROR: could not open window with GLFW3\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(glWindow);

	glfwWindowHint(GLFW_SAMPLES, 4);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "OpenGL version supported: " << version << "\n";

	Input::RegisterCallbacks(glWindow);

	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glViewport(0, 0, Width, Height);
	glEnable(GL_DEPTH_TEST);
}

void Window::Update()
{
	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
	}

	glfwPollEvents();
	glfwSwapBuffers(glWindow);
}
