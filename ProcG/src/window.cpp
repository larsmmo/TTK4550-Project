#include <iostream>
#include "window.hpp"
#include "glfwWindow.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Window* Window::create(const Config& cfg)
{
	if (cfg.windowSystem == "GLFW")
	{
		return new GLFWWindow(cfg);
	}
	else
	{
		printf("Invalid or unsupported windowing system");
		return NULL;
	}
}
