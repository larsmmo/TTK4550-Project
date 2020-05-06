#pragma once
#include "config.h"
#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLFW_Window : public Window
{
private:
	GLFWwindow* mWindow;

public:
	GLFW_Window(const Config& cfg);
	~GLFW_Window();

	unsigned int getWindowWidth();
	unsigned int getWindowHeight();

	void swapDrawBuffers();
	void pollEvents();
	bool shouldClose();
};