
#include "context.hpp"
#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLFW window callback function for handling keyboard button input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	camera.handleKeyboardInputs(key, action);
}

OpenGLContext::OpenGLContext(const Config& cfg)
{
	// Initializing GLFW			// TODO: move to window class
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

	//Create window
	mWindowWidth = cfg.windowWidth;
	mWindowHeight = cfg.windowHeight;

	mWindow = glfwCreateWindow(mWindowWidth,
		mWindowHeight,
		cfg.windowTitle.c_str(),
		nullptr,
		nullptr);
	if (!mWindow)
	{
		fprintf(stderr, "ERROR: Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make the context of the window be the main context of current thread
	glfwMakeContextCurrent(mWindow);

	// Set up callback functions for input
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(mWindow, mouseCallback);
	glfwSetMouseButtonCallback(mWindow, mouseButtonCallback);
	glfwSetKeyCallback(mWindow, keyCallback);

	// Initialize GLAD
	gladLoadGL();

	glViewport(0, 0, mWindowWidth, mWindowHeight);

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

void OpenGLContext::setViewport(int setWindowWidth, int setWindowHeight)
{
	glViewport(0, 0, setWindowWidth, setWindowHeight);
}

void OpenGLContext::clearBuffers()
{
	// Clear colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::processKeyboardInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}
}

bool OpenGLContext::shouldClose()
{
	return glfwWindowShouldClose(mWindow);
}
