#include "engine.hpp"
#include "shader.hpp"
#include "shapes.h"
#include "glUtilities.h"
#include "utilities/windowSettings.h"
#include "utilities/timeUtilities.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void runEngine(GLFWwindow* window)
{
	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Clear color buffer and set default color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while(!glfwWindowShouldClose(window))
	{
		// Clear colour and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update and render a frame
		updateFrame(window);
		renderFrame(window);

		glfwSwapBuffers(window);

		// Check if any events have been triggered (mouse, keyboard...)
		glfwPollEvents();
		processKeyboardInput(window);
	}
}

void processKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}