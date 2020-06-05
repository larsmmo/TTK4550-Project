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

#include <cstdlib>
#include <string>

Scene::Scene()
{
	rootNode = createSceneNode();
	float rootPos =rootnode.getPosition();

	static SceneNode* groundNode;
	static SceneNode* boxNode;

	groundNode = createSceneNode();
	boxNode = createSceneNode();

	const glm::vec3 groundDimensions(30, 1, 90);
	const glm::vec3 boxDimensions(40, 40, 40);

	Mesh ground = cube(groundDimensions, glm::vec2(90), true, true);
	Mesh box = cube(boxDimensions, glm::vec2(40), true, true);

	unsigned int groundVAO = generateVAO(ground);
	unsigned int boxVAO = generateVAO(box);

	// Using vectors instead. Fixing later...
	activePointLights = 1;

	// Create some light sources and place them in the scene
	for (unsigned int light = 0; light < activePointLights; light++) {
		PointLightSource pointLight;
		pointLight.lightNode = createSceneNode();
		pointLight.lightNode->vertexArrayObjectID = light;
		pointLight.lightNode->nodeType = POINT_LIGHT;
		pointLight.color[light] = 1.0;
		groundNode->children.push_back(pointLight.lightNode);
		pointLightSources.push_back(pointLight);
	}

	rootNode->children.push_back(groundNode);
	groundNode->children.push_back(boxNode);

	groundNode->vertexArrayObjectID = groundVAO;
	groundNode->VAOIndexCount = ground.indices.size();

	boxNode->vertexArrayObjectID = boxVAO;
	boxNode->VAOIndexCount = box.indices.size();

	// Set up cubemap and frame buffer for shadow mapping
	//glGenFramebuffers(1, &depthMapFrameBuffer);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	printf("Created scene");
}
