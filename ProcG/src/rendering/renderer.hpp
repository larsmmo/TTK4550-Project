#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "camera.hpp"
#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
	ProcG::Camera* camera;
	ProcG::Shader* shader;

public:
	void renderNode(SceneNode* node);
	void renderFrame(GLFWwindow* window);
};


#endif