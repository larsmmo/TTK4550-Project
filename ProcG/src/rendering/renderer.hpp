#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "context.hpp"
#include "config.h"
#include "window.hpp"
#include "camera.hpp"
#include "utilities\timeUtilities.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
	Context* mRenderContext;
	ProcG::Shader* mShader;		// Should be heap allocated
	ProcG::Camera* mCamera;
	Window* mWindow;

public:
	Renderer();
	bool draw(SceneNode* rootNode);
	void updateFrame(SceneNode* rootNode);
	void renderFrame(SceneNode* rootNode);
	void renderNode(SceneNode* node);
};


#endif