#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "sceneGraph.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct LightSource {
	SceneNode* lightNode;
	glm::vec3 color;
};

/* The Scene class is responsible for setting up and updating scenes before being rendered */
class Scene
{
private:
	SceneNode* rootNode;
	std::vector<LightSource> lightSources;
	unsigned int activeLights;

public:
	Scene();
	//void loadScene();
	SceneNode* getScene();
	unsigned int getActiveLights();
	void updateScene();
};

#endif