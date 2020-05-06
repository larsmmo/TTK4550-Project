#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#pragma once

#include "config.h"
#include "window.hpp"
#include "sceneGraph.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// (Factory pattern)

class Context
{
protected:

public:
	static Context* create(Window* window, const Config& cfg);

	virtual void setViewport(int setWindowWidth, int setWindowHeight) = 0;
	virtual void clearBuffers() = 0;
	//virtual void bindTexture() = 0;
	virtual void drawGeometry(SceneNode* node) = 0;
};


#endif