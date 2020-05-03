#include "application.hpp"
#include "rendering/shader.hpp"
#include "shapes.h"
#include "utilities/timeUtilities.h"
#include "config.h"
#include "rendering\renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Application::Application()
{
	mRenderer = Renderer();

}

