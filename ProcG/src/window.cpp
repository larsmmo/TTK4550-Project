#include <iostream>
#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Callback function for letting GLFW report errors as they occur
static void glfwErrorCallback(int err, const char* description)
{
	fprintf(stderr, "GLFW error: \n \t%s (%i)\n", description, err);
}

// GLFW window callback function for handling mouse position input			// Move these to window class
void mouseCallback(GLFWwindow* window, double x, double y)
{
	camera.handleCursorPosInput(x, y);
	//glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

// GLFW window callback function for handling mouse button input
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	camera.handleMouseButtonInputs(button, action);
}

/* Updates and returns the height of the window*/
unsigned int GLFWWindow::getWindowHeight()
{
	glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	return mWindowHeight;
}

/* Updates and returns the width of the window*/
unsigned int GLFWWindow::getWindowWidth()
{
	glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	return mWindowWidth;
}

void GLFWWindow::swapDrawBuffers()
{
	glfwSwapBuffers(mWindow);
}

void GLFWWindow::pollEvents()
{
	glfwPollEvents();
}

bool GLFWWindow::shouldClose()
{
	return glfwWindowShouldClose(mWindow);
}
