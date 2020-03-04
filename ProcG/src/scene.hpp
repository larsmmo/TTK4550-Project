#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "sceneGraph.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct LightSource {
	SceneNode* lightNode;
	glm::vec3 worldPos;
	glm::vec3 color;
};

class Scene
{
private:
	SceneNode* rootNode;
	//std::vector<LightSource> lightSources;
	//int activeLights;
	Scene();

public:
	void updateScene();
};

#endif