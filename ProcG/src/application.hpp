#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once

#include "sceneGraph.hpp"
#include "rendering/renderer.hpp"
#include "config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
private:
	Renderer mRenderer;

public:
	Application();
	void runApplication();

};

#endif