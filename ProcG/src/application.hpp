#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once

#include "rendering/renderer.hpp"
#include "config.h"

class Application
{
private:
	Renderer mRenderer;

public:
	Application();
	void runApplication();

};

#endif