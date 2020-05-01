#include "renderer.hpp"
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

Renderer::Renderer(const Config& cfg)
{
	mRenderContext = Context::create(cfg);
}

void Renderer::updateFrame()
{

}

/* Renders a scene from objects in a Scene Graph */
void Renderer::renderScene(SceneNode* rootNode)
{
	int windowWidth = mRenderContext->getWindowWidth();
	int windowHeight = mRenderContext->getWindowHeight();
	mRenderContext->setViewport(windowWidth, windowHeight);

	renderNode(rootNode);
}




void Renderer::draw()
{
	while (!glfwWindowShouldClose(window))
	{
		// Clear colour and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update and render a frame
		updateFrame(window);
		renderFrame(window);

		glfwSwapBuffers(window);

		// Check if any events have been triggered (mouse, keyboard...)
		glfwPollEvents();
		processKeyboardInput(window);
	}
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
