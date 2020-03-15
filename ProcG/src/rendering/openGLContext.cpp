
#include "context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


openGLContext::openGLContext(const Config& config)
{
	// Initializing GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Error: GLFW did not start\n");
		exit(EXIT_FAILURE);
	}

	// Set core window options (OpenGL 4.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Enable Multisample anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, windowSamples);

	glfwSetErrorCallback(glfwErrorCallback);

	GLFWwindow* window = glfwCreateWindow(windowWidth,
		windowHeight,
		windowTitle.c_str(),
		nullptr,
		nullptr);
	if (!window)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make the context of the window be the main context of current thread
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	gladLoadGL();

	glViewport(0, 0, windowWidth, windowHeight);

	// Show info about OpenGL
	printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	printf("GLFW version\t %s\n", glfwGetVersionString());
	printf("OpenGL version\t %s\n", glGetString(GL_VERSION));
	printf("GLSL version\t %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

