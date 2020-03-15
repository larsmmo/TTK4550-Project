#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "camera.hpp"
#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Effects
{
private:
	ProcG::Camera* camera;
	ProcG::Shader* shader;

	void renderShadows();

public:
	void renderShadows();
};


#endif