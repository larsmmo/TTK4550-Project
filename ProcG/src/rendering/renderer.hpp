#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
	Context mRenderContext;
	//void renderEffects();

public:
	Renderer();
	void renderNode(SceneNode* node);
	void renderScene(SceneNode* scene);
	bool isContextOpen();
};


#endif