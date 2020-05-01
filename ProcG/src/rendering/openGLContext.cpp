
#include "context.hpp"
#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Callback function for letting GLFW report errors as they occur
static void glfwErrorCallback(int err, const char* description)
{
	fprintf(stderr, "GLFW error: \n \t%s (%i)\n", description, err);
}

OpenGLContext::OpenGLContext(const Config& cfg)
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
	glfwWindowHint(GLFW_SAMPLES, cfg.windowSamples);

	glfwSetErrorCallback(glfwErrorCallback);

	GLFWwindow* window = glfwCreateWindow(cfg.windowWidth,
		cfg.windowHeight,
		cfg.windowTitle.c_str(),
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

	glViewport(0, 0, cfg.windowWidth, cfg.windowHeight);

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Clear color buffer and set default color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Show info about OpenGL
	printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	printf("GLFW version\t %s\n", glfwGetVersionString());
	printf("OpenGL version\t %s\n", glGetString(GL_VERSION));
	printf("GLSL version\t %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

OpenGLContext::~OpenGLContext()
{
	// Delete all of GLFW's allocated resources
	glfwTerminate();
}

void OpenGLContext::processKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}