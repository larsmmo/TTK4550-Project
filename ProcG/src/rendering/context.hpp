#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#pragma once

#include "config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// (Builder pattern)

template <class T>
class Context
{
private:
	T* window;

protected:

public:
	Context(const Config& config);
	virtual unsigned int getWindowHeight() {};
	virtual unsigned int getWindowWidth() {};
	bool isOpen();
};


#endif