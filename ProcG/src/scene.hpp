#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "sceneGraph.hpp"

struct LightSource {
	SceneNode* lightNode;
	glm::vec3 color;
};

/* Scene structure which contains everything needed for rendering */
struct Scene			// TODO: MAKE scenemanager
{
	SceneNode* rootNode;

	std::vector<LightSource> lightSources;

	unsigned int activeLights;
};

#endif