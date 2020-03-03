#ifndef ENGINE_HPP
#define ENGINE_HPP
#pragma once

#include "sceneGraph.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
private:
	static Engine* engineInstance;
	Engine(GLFWwindow* window);
	GLFWwindow* window;
	SceneNode* sceneRootNode;

public:
	static void runEngine(GLFWwindow* window);
};

void processKeyboardInput(GLFWwindow* window);

#endif