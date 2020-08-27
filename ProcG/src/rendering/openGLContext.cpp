
#include "context.hpp"
#include "window.hpp"
#include "OpenGLContext.hpp"
#include "sceneGraph.hpp"
#include "texture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


OpenGLContext::OpenGLContext(Window* window)
{
	// Initialize GLAD
	gladLoadGL();

	glViewport(0, 0, window->getWindowWidth(), window->getWindowHeight());

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Clear color buffer and set default color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Show info about OpenGL
	printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	printf("GLFW version\t %s\n", glfwGetVersionString());
	printf("OpenGL version\t %s\n", glGetString(GL_VERSION));
	printf("GLSL version\t %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

/*
OpenGLContext::~OpenGLContext()
{
	
}*/

void OpenGLContext::setViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void OpenGLContext::clearBuffers()
{
	// Clear colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int OpenGLContext::setupTexture(int height, int width, int depth, unsigned char* data, bool mipMapping, int textureID)
{
	Texture texture;
	if (depth = 0)
	{
		texture.generate(height, width, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, mipMapping, data);
		return texture.getID();
	}
	else {
		texture.generate(height, width, depth, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, mipMapping, data);
		return texture.getID();
	}
}

void OpenGLContext::drawGeometry(unsigned int VAOID, unsigned int VAOIndexCount, int textureID)
{
	glBindVertexArray(VAOID);
	if (textureID != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	glDrawElements(GL_TRIANGLES, VAOIndexCount, GL_UNSIGNED_INT, nullptr);
}
