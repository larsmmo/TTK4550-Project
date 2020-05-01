#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "config.h"
#include "context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLContext : public Context
{
private:
	static GLFWwindow* window;

public:
	OpenGLContext(const Config& cfg);
	~OpenGLContext();
	unsigned int getWindowHeight();
	unsigned int getWindowWidth();
	bool isOpen();
	void processKeyboardInput(GLFWwindow* window);
};


#endif