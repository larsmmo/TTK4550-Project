#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "sceneGraph.hpp"

struct LightSource {
	SceneNode* lightNode;
	glm::vec3 color;
};

/* Scene structure which contains scene information for rendering */
struct Scene			// TODO: MAKE scenemanager
{
	Scene();
	SceneNode* rootNode;

	std::vector<LightSource> lightSources;

	unsigned int activeLights;
};

#endif