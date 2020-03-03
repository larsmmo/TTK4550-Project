// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "../windowSettings.h"

// Standard headers
#include <cstdlib>
#include <string>

GLFWwindow* window_init()
{
	// Initializing GLFW
	if (!glfwInit())
	{
		//fprintf(stderr, "GLFW could not start\n");
		//exit(EXIT_FAILURE);
	}

	// Set core window options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth,
										  windowHeight,
										  windowTitle.c_str(),
										  nullptr,
										  nullptr);
}

int main(int argc, char* argb[])
{
	// Initialize window using GLFW
	GLFWwindow* window = window_init();

	// Run an OpenGL application using this window
	//runProgram(window);

	// Terminate GLFW (no need to call glfwDestroyWindow)
	//glfwTerminate();

	return EXIT_SUCCESS;
}
