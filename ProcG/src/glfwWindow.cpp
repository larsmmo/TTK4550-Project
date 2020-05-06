#include <iostream>
#include "glfwWindow.hpp"
#include "window.hpp"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Callback function for letting GLFW report errors as they occur
static void glfwErrorCallback(int err, const char* description)
{
	fprintf(stderr, "GLFW error: \n \t%s (%i)\n", description, err);
}

// GLFW window callback function for handling keyboard button input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//camera.handleKeyboardInputs(key, action);
}

// GLFW window callback function for handling mouse position input			
void mouseCallback(GLFWwindow* window, double x, double y)
{
	//camera.handleCursorPosInput(x, y);							// TODO: Move camera dependency
	//glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

// GLFW window callback function for handling mouse button input
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//camera.handleMouseButtonInputs(button, action);
}

GLFW_Window::GLFW_Window(const Config& cfg)
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

	printf("CREATING WINDOW \n");
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
}

GLFW_Window::~GLFW_Window()
{
	// Delete all of GLFW's allocated resources
	glfwTerminate();
}

/* Updates and returns the height of the window*/
unsigned int GLFW_Window::getWindowHeight()
{
	glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	return mWindowHeight;
}

/* Updates and returns the width of the window*/
unsigned int GLFW_Window::getWindowWidth()
{
	glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	return mWindowWidth;
}

void GLFW_Window::swapDrawBuffers()
{
	glfwSwapBuffers(mWindow);
}

void GLFW_Window::pollEvents()
{
	glfwPollEvents();
}

bool GLFW_Window::shouldClose()
{
	return glfwWindowShouldClose(mWindow);
}
