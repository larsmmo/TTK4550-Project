#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#pragma once

#include "config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// (Factory pattern)

class Context
{
protected:

public:
	static Context* create(const Config& cfg);
	virtual unsigned int getWindowHeight() = 0;
	virtual unsigned int getWindowWidth() = 0;
	virtual bool isOpen() = 0;
	virtual void setViewport(int setWindowWidth, int setWindowHeight) = 0;

	virtual void processKeyboardInput() = 0;
};


#endif