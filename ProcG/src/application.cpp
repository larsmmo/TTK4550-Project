#include "application.hpp"
#include "config.h"
#include "rendering\renderer.hpp"
#include "sceneManager.hpp"

#include <iostream>


Application::Application()
{
	
}

void Application::runApplication()
{
	// Set up test scene to be rendered
	SceneManager currentScene(&mResourceManager);
	mRenderer.draw(&currentScene);		// Enter draw loop
}

