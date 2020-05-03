// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "config.h"
#include "application.hpp"

// Standard headers
#include <cstdlib>
#include <string>

// Callback function for letting GLFW report errors as they occur
static void glfwErrorCallback(int err, const char* description)
{
	fprintf(stderr, "GLFW error: \n \t%s (%i)\n", description, err);
}


int main(int argc, char* argb[])
{
	Config cfg;

	Application app = Application(cfg);


	return EXIT_SUCCESS;
}
