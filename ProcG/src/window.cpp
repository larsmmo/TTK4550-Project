#include <iostream>
#include "window.hpp"
#include "glfwWindow.hpp"
#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Window* Window::create(const Config& cfg, ProcG::Camera* camera)
{
	if (cfg.windowSystem == "GLFW")
	{
		printf("creating window");
		return new GLFW_Window(cfg, camera);
	}
	else
	{
		printf("Invalid or unsupported windowing system");
		return NULL;
	}
}
