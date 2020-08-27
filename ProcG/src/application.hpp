#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once

#include "resourceManager.hpp"
#include "rendering/renderer.hpp"
#include "sceneManager.hpp"
#include "config.h"

class Application
{
private:
	Renderer mRenderer;
	//SceneManager mSceneManager;
	ResourceManager mResourceManager;

public:
	Application();
	void runApplication();

};

#endif