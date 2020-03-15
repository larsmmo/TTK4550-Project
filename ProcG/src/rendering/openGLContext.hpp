#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// (Builder pattern)

template <class T>
class openGLContext : Context
{
public:
	openGLContext(const Config& config);
	virtual unsigned int getWindowHeight();
	virtual unsigned int getWindowWidth();
	bool isOpen();
};


#endif