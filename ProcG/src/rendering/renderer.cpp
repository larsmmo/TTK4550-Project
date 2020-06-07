#include "renderer.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "glUtilities.h"
#include "scene.hpp"
#include "sceneGraph.hpp"
#include "utilities/timeUtilities.h"
#include "camera.hpp"

#include <fmt/format.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
	Config cfg;								// TODO: add proper config file system

	mCamera = new ProcG::Camera(glm::vec3(0.0f, 0.0f, -5.0f));
	mWindow = Window::create(cfg, mCamera);
	mRenderContext = Context::create(mWindow, cfg);

	// Create shader program				// TODO: Move this part into a shaderManager
	mShader = new ProcG::Shader();
	std::vector<std::string> basicShaderFiles{ "../res/shaders/simple.vert", "../res/shaders/simple.frag" };
	mShader->makeBasicShader(basicShaderFiles);
	mShader->activate();

}

void Renderer::updateFrame(Scene* scene)
{
	double timeDelta = getTimeDeltaSeconds();

	// Update camera and send its position to the shader
	mCamera->updateCamera(timeDelta);
	mShader->setUniform3fv("cameraPosition", glm::value_ptr(mCamera->getPosition()));

	// Calculate VP matrix and MVP matrix for all scene nodes
	glm::mat4 projection = glm::perspective(glm::radians(80.0f), float(mWindow->getWindowWidth()) / float(mWindow->getWindowHeight()), 0.1f, 350.f);
	glm::mat4 viewProjection = projection * mCamera->getViewMatrix();

	updateSceneNodeTransformations(scene->rootNode, glm::mat4(1.0f), viewProjection);

	// Update light positions and colors, then send to shader
	mShader->setUniform1i("activePointLights", scene->activePointLights);
	
	for (unsigned int light = 0; light < scene->activePointLights; light++)
	{
		//mShader->setLightSourceUniforms(light, scene->lightSources[light]->lightNode.currentTransformationMatrix);
		mShader->setUniform3fv(fmt::format("pointLights[{}].color", light), glm::value_ptr(scene->pointLightSources[light].color));
	}
}


/* Renders a scene from objects in a Scene Graph */
void Renderer::renderFrame(Scene* scene)
{
	int windowWidth = mWindow->getWindowWidth();
	int windowHeight = mWindow->getWindowHeight();
	mRenderContext->setViewport(windowWidth, windowHeight);

	renderNode(scene->rootNode);
}


bool Renderer::draw(Scene* scene)			// TODO: change to per-node drawing
{
	while (!mWindow->shouldClose())
	{
		// Clear colour and depth buffers
		mRenderContext->clearBuffers();

		// Update and render a frame with scene information
		updateFrame(scene);
		renderFrame(scene);

		mWindow->swapDrawBuffers();

		// Check if the window has captured any events
		mWindow->pollEvents();
	}
	return true;
}

/* Render an object using a scene graph*/
void Renderer::renderNode(SceneNode* node)
{
	// Update uniforms for currently activated shader
	mShader->setUniformMatrix4fv("MVP", false, glm::value_ptr(node->MVPMatrix));
	mShader->setUniformMatrix4fv("modelMatrix", false, glm::value_ptr(node->currentTransformationMatrix));

	glm::mat3 normalMatrix = glm::mat3(transpose(inverse(node->currentTransformationMatrix)));
	mShader->setUniformMatrix3fv("normalMatrix", false, glm::value_ptr(normalMatrix));

	node->material->getShader()->setUniformMatrix4fv("MVP", false, glm::value_ptr(node->MVPMatrix));

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
		//mShader->setUniform3fv(fmt::format("pointLights[{}].color", node->vertexArrayObjectID), glm::value_ptr(
		break;
		}
	case SPOT_LIGHT: break;
	}

	for (SceneNode* child : node->children) {
		renderNode(child);
	}
}

