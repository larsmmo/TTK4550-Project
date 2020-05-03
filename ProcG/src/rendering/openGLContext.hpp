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
	static GLFWwindow* mWindow;
	int mWindowHeight;
	int mWindowWidth;

public:
	OpenGLContext(const Config& cfg);
	~OpenGLContext();
	unsigned int getWindowHeight();
	unsigned int getWindowWidth();
	void setViewport(int setWindowWidth, int setWindowHeight);
	void clearBuffers();
	void swapDrawBuffers();
	void pollEvents();
	void processKeyboardInput();
	bool shouldClose();
};


#endif