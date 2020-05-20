#include "application.hpp"
#include "config.h"
#include "rendering\renderer.hpp"
#include "scene.hpp"

#include <iostream>


Application::Application()
{
	
}

void Application::runApplication()
{
	// Set up test scene to be rendered
	Scene currentScene;

	while (mRenderer.draw(&currentScene)) {};		// temporary draw loop
}

