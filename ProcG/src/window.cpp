#include <iostream>
#include "window.hpp"
#include "glfwWindow.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Window* Window::create(const Config& cfg)
{
	if (cfg.windowSystem == "GLFW")
	{
		printf("creat window");
		return new GLFW_Window(cfg);
	}
	else
	{
		printf("Invalid or unsupported windowing system");
		return NULL;
	}
}
