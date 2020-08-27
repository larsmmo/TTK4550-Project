#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#pragma once

#include "sceneGraph.hpp"
#include "resourceManager.hpp"

struct DirectionalLightSource {
	SceneNode* lightNode;
	glm::vec3 color;
	glm::vec3 direction;
};

struct PointLightSource {
	SceneNode* lightNode;
	glm::vec3 color;
};

/* Structure which contains scene information for rendering */
class SceneManager
{
private:
	ResourceManager* mResourceManager;
	void createSkyBox(int height, int width, int depth);

public:
	SceneManager(ResourceManager* resourceManager);
	~SceneManager();
	SceneNode* rootNode;

	std::vector<PointLightSource> pointLightSources;
	std::vector<DirectionalLightSource> directionalLightSources;

	unsigned int activePointLights;
	unsigned int activeDirectionalLights;
};

#endif