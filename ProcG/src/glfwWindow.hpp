#pragma once
#include "config.h"
#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLFW_Window : public Window
{
private:
	GLFWwindow* mWindow;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseCallback(GLFWwindow* window, double x, double y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
	GLFW_Window(const Config& cfg);
	~GLFW_Window();

	unsigned int getWindowWidth();
	unsigned int getWindowHeight();

	void swapDrawBuffers();
	void pollEvents();
	bool shouldClose();
};