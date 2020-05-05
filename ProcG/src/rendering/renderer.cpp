#include "renderer.hpp"
#include "window.hpp"
#include "sceneGraph.hpp"
#include "shader.hpp"
#include "glUtilities.h"
#include "sceneGraph.hpp"
#include "utilities/timeUtilities.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
	Config cfg;					// TODO: add proper config file system
	mWindow = Window::create(cfg);
	mRenderContext = Context::create(mWindow, cfg);
}

void Renderer::updateFrame(SceneNode* rootNode)
{

}


/* Renders a scene from objects in a Scene Graph */
void Renderer::renderFrame(SceneNode* rootNode)
{
	int windowWidth = mWindow->getWindowWidth();
	int windowHeight = mWindow->getWindowHeight();
	mRenderContext->setViewport(windowWidth, windowHeight);

	renderNode(rootNode);
}


bool Renderer::draw(SceneNode* rootNode)			// TODO: change to per-node drawing
{
	while (!mWindow->shouldClose())
	{
		// Clear colour and depth buffers
		mRenderContext->clearBuffers();

		// Update and render a frame
		updateFrame(rootNode);
		renderFrame(rootNode);

		mWindow->swapDrawBuffers();

		// Check if window has captured any events happening
		mWindow->pollEvents();
	}

	return true;
}


void Renderer::renderNode(SceneNode* node)
{
	// Send uniforms to currently activated shader
	glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(node->MVPMatrix));
	glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(node->currentTransformationMatrix));
	glm::mat3 normalMatrix = glm::mat3(transpose(inverse(node->currentTransformationMatrix)));
	glUniformMatrix3fv(5, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	switch (node->nodeType) 
	{
	case GEOMETRY:
		if (node->vertexArrayObjectID != -1) {
			glBindVertexArray(node->vertexArrayObjectID);
			glDrawElements(GL_TRIANGLES, node->VAOIndexCount, GL_UNSIGNED_INT, nullptr);
		}
		break;
	case POINT_LIGHT:
		{
		GLint location_position = shader->getUniformFromName(fmt::format("pointLights[{}].position", node->vertexArrayObjectID));		// Vertex array obj ID = light ID
		glUniform3fv(location_position, 1, glm::value_ptr(lightSources[node->vertexArrayObjectID].worldPos));

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

