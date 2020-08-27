#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "config.h"
#include "context.hpp"
#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLContext : public Context
{
private:

public:
	OpenGLContext(Window* window);
	~OpenGLContext();

	void setViewport(int width, int height);
	void clearBuffers();
	unsigned int setupTexture(int height, int width, int depth, unsigned char* data, bool mipMapping, int textureID);
	void drawGeometry(unsigned int VAOID, unsigned int VAOIndexCount, int textureID);

};


#endif