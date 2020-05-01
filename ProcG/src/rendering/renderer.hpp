#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "context.hpp"
#include "config.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
	Context* mRenderContext;
	//void renderEffects();

public:
	Renderer(const Config& cfg);
	void draw();
	void renderScene(SceneNode* rootNode);
	void updateFrame();
	void renderNode(SceneNode* node);
	bool isContextOpen();
};


#endif