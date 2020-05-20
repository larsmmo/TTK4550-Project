// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "scene.hpp"
#include "rendering/shader.hpp"
#include "sceneGraph.hpp"
#include "mesh.h"
#include "shapes.h"
#include "rendering/glUtilities.h"

// Standard headers
#include <cstdlib>
#include <string>

Scene::Scene()
{
	rootNode = createSceneNode();

	SceneNode* groundNode;
	SceneNode* boxNode;

	groundNode = createSceneNode();
	boxNode = createSceneNode();

	const glm::vec3 groundDimensions(180, 1, 90);
	const glm::vec3 boxDimensions(40, 40, 40);

	Mesh ground = cube(groundDimensions, glm::vec2(90), true, true);
	Mesh box = cube(boxDimensions, glm::vec2(40), true, true);

	unsigned int groundVAO = generateVAO(ground);
	unsigned int boxVAO = generateVAO(box);

	// Using vectors instead. Fixing later...
	int activeLights = 3;
	LightSource lightSources[3];

	// Create some light sources
	for (int light = 0; light < activeLights; light++) {
		lightSources[light].lightNode = createSceneNode();
		lightSources[light].lightNode->vertexArrayObjectID = light;
		lightSources[light].lightNode->nodeType = POINT_LIGHT;
		lightSources[light].color[light] = 1.0;
		groundNode->children.push_back(lightSources[light].lightNode);
	}

	rootNode->children.push_back(groundNode);
	groundNode->children.push_back(boxNode);

	groundNode->vertexArrayObjectID = groundVAO;
	groundNode->VAOIndexCount = ground.indices.size();

	boxNode->vertexArrayObjectID = boxVAO;
	boxNode->VAOIndexCount = box.indices.size();

	// Send number of lights in the ON-state to the shader
	glUniform1i(6, activeLights);

	// Set up cubemap and frame buffer for shadow mapping
	//glGenFramebuffers(1, &depthMapFrameBuffer);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

SceneNode* Scene::getScene() {
	return rootNode;
}

unsigned int Scene::getActiveLights() {
	return activeLights;
}

void Scene::updateScene()
{
	
}