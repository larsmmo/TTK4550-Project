#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <glad/glad.h>

#include <string>

struct Config {
	const std::string	graphicsAPI = "OpenGL";
	const std::string	windowSystem = "GLFW";
	const int			windowWidth = 1600;
	const int			windowHeight = 720;
	const std::string	windowTitle = "OpenGL Window";
	const GLint			windowResizable = GL_FALSE;
	const int			windowSamples = 4;
};

#endif