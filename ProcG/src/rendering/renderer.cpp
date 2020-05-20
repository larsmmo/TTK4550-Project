#include "renderer.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "glUtilities.h"
#include "scene.hpp"
#include "sceneGraph.hpp"
#include "utilities/timeUtilities.h"
#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
	Config cfg;								// TODO: add proper config file system
	mWindow = Window::create(cfg);
	mRenderContext = Context::create(mWindow, cfg);

	// Create shader program				// TODO: Move this part into a shaderManager
	mShader = new ProcG::Shader();			// see if I can change this part also
	std::vector<std::string> basicShaderFiles{ "../res/shaders/simple.vert", "../res/shaders/simple.frag" };
	mShader->makeBasicShader(basicShaderFiles);
	mShader->activate();

	mCamera = new ProcG::Camera();
}

void Renderer::updateFrame(Scene* scene)
{
	double timeDelta = getTimeDeltaSeconds();

	// Update camera and send its position to shader
	mCamera->updateCamera(timeDelta);
	mShader->setUniform3fv("cameraPosition", glm::value_ptr(mCamera->getPosition()));

	// Update light positions and colors and send to shader
	mShader->setUniform1i("activeLights", scene->getActiveLights());
	for (unsigned int light = 0; light < scene->getActiveLights(); light++)
	{
		mShader->setLightSourceUniforms(light, )
	}

	// Calculate VP matrix and MVP matrix for all scene nodes
	glm::mat4 projection = glm::perspective(glm::radians(80.0f), float(mWindow->getWindowWidth()) / float(mWindow->getWindowHeight()), 0.1f, 350.f);
	glm::mat4 ViewProjection = projection * mCamera->getViewMatrix();

	updateSceneNodeTransformations(scene->getScene(), glm::mat4(1.0f), ViewProjection);
}


/* Renders a scene from objects in a Scene Graph */
void Renderer::renderFrame(SceneNode* rootNode)
{
	int windowWidth = mWindow->getWindowWidth();
	int windowHeight = mWindow->getWindowHeight();
	mRenderContext->setViewport(windowWidth, windowHeight);

	renderNode(rootNode);
}


bool Renderer::draw(Scene* scene)			// TODO: change to per-node drawing
{
	while (!mWindow->shouldClose())
	{
		// Clear colour and depth buffers
		mRenderContext->clearBuffers();

		// Update and render a frame with scene information
		updateFrame(scene);
		renderFrame(scene->getScene());

		mWindow->swapDrawBuffers();

		// Check if window has captured any events
		mWindow->pollEvents();
	}
	return true;
}

void Renderer::renderNode(SceneNode* node)
{
	// Update uniforms for currently activated shader
	mShader->setUniformMatrix4fv("MVP", false, glm::value_ptr(node->MVPMatrix));
	mShader->setUniformMatrix4fv("modelMatrix", false, glm::value_ptr(node->currentTransformationMatrix));

	glm::mat3 normalMatrix = glm::mat3(transpose(inverse(node->currentTransformationMatrix)));
	mShader->setUniformMatrix3fv("normalMatrix", false, glm::value_ptr(normalMatrix));

	switch (node->nodeType)				// Maybe implement as iterator or strategy pattern instead
	{
	case GEOMETRY:
		if (node->vertexArrayObjectID != -1) {
			mRenderContext->drawGeometry(node);
		}
		break;
	case POINT_LIGHT:
		{
		// Calculate world coordinates of point lights and send them to the active shader
		mShader->setUniform3fv(fmt::format("pointLights[{}].position", node->vertexArrayObjectID), glm::value_ptr(glm::vec3(node->currentTransformationMatrix * glm::vec4(0, 0, 0, 1.0))));
		mShader->setUniform3fv(fmt::format("pointLights[{}].color", node->vertexArrayObjectID), glm::value_ptr(
		GLint location_color = shader->getUniformFromName(fmt::format("pointLights[{}].color", node->vertexArrayObjectID));
		glUniform3fv(location_color, 1, glm::value_ptr(lightSources[node->vertexArrayObjectID].color));
		break;
		}
	case SPOT_LIGHT: break;
	}

	for (SceneNode* child : node->children) {
		renderNode(child);
	}
}

