// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "scene.hpp"
#include "rendering/shader.hpp"
#include "utilities/windowSettings.h"
#include "rendering/engine.hpp"
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

	// Create some funky light sources
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
	glGenFramebuffers(1, &depthMapFrameBuffer);

	// Each of the 6 faces is a 2D depth-value texture
	for (int light = 0; light < numLights; light++) {
		glGenTextures(1, &depthCubemap[light]);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap[light]);
		for (unsigned int i = 0; i < 6; ++i) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);		// create textures
		}
		// Set texture parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// Attach cubemap as the depth attachment of the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap[light], 0);

		// Tell OpenGL not to not render to color buffer (only need depth values)
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		// Tell OpenGL which texture unit each sampler belongs to (I should learn how to put everything into one texture. For next time maybe..)
		GLint location_sampler = shader->getUniformFromName(fmt::format("depthMap[{}]", light));
		glUniform1i(location_sampler, light);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Scene::updateScene()
{
	
}