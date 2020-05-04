#include "context.hpp"
#include "openGLContext.hpp"
#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Context* Context::create(const Config& cfg)
{
	if (cfg.graphicsAPI == "OpenGL")
	{

		return new OpenGLContext(cfg);
		// TODO: also create window here?
	}
	else
	{
		printf("Invalid or unsupported graphics API");
		return NULL;
	}
}