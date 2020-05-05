#pragma once
#include "config.h"
#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLFWWindow : public Window
{
private:
	static GLFWwindow* mWindow;

public:
	GLFWWindow(const Config& cfg);
	~GLFWWindow();

	unsigned int getWindowWidth();
	unsigned int getWindowHeight();

	void swapDrawBuffers();
	void pollEvents();
	bool shouldClose();
};