#ifndef RENDERER_HPP
#define RENDERER_HPP
#pragma once

#include "sceneManager.hpp"
#include "sceneGraph.hpp"
#include "shader.hpp"
#include "context.hpp"
#include "config.h"
#include "window.hpp"
#include "camera.hpp"
#include "texture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Renderer
{
private:
	Context* mRenderContext;
	ProcG::Shader* mShader;		// Heap allocated
	ProcG::Shader* mSkyShader;
	ProcG::Camera* mCamera;
	Window* mWindow;

	std::vector<Texture> mTextures;

public:
	Renderer();

	void setupTexture(int height, int width, unsigned char* data, SceneNode* node);
	void renderSky();
	bool draw(SceneManager* scene);
	void updateFrame(SceneManager* scene);
	void renderFrame(SceneManager* scene);
	void renderNode(SceneNode* node);
};


#endif