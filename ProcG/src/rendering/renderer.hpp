#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "context.hpp"
#include "config.h"
#include "window.hpp"
#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
private:
	Context* mRenderContext;
	ProcG::Shader* mShader;		// Heap allocated
	ProcG::Camera* mCamera;
	Window* mWindow;

public:
	Renderer();
	bool draw(Scene* scene);
	void updateFrame(Scene* scene);
	void renderFrame(Scene* scene);
	void renderNode(SceneNode* node);
};


#endif