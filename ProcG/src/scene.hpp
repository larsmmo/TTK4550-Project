#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "sceneGraph.hpp"


struct PointLightSource {
	SceneNode* lightNode;
	glm::vec3 color;
};

/* Structure which contains scene information for rendering */
struct Scene
{
	Scene();
	SceneNode* rootNode;

	std::vector<PointLightSource> pointLightSources;

	unsigned int activePointLights;
	unsigned int activeDirectionalLights;
};

#endif