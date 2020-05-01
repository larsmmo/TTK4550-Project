#include "context.hpp"
#include "openGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Context* Context::create(const Config& cfg)
{
	if (cfg.graphicsAPI == "OpenGL")
	{
		return new OpenGLContext(cfg);
	}
	else
	{
		printf("Invalid or unsupported graphics API");
		return NULL;
	}
}