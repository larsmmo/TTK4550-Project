// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "config.h"
#include "application.hpp"

// Standard headers
#include <cstdlib>
#include <string>


int main(int argc, char* argb[])
{
	Application app = Application();

	app.runApplication();

	return EXIT_SUCCESS;
}
