#pragma once
#include "config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
protected:
	int mWindowHeight;
	int mWindowWidth;
public:
	static Window* create(const Config& cfg);

	virtual unsigned int getWindowWidth() = 0;
	virtual unsigned int getWindowHeight() = 0;

	virtual void swapDrawBuffers() = 0;
	virtual void pollEvents() = 0;
	virtual bool shouldClose() = 0;
};