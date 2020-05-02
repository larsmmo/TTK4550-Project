
#include "context.hpp"
#include "OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Callback function for letting GLFW report errors as they occur
static void glfwErrorCallback(int err, const char* description)
{
	fprintf(stderr, "GLFW error: \n \t%s (%i)\n", description, err);
}

OpenGLContext::OpenGLContext(const Config& cfg)
{
	// Initializing GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Error: GLFW did not start\n");
		exit(EXIT_FAILURE);
	}

	// Set core window options (OpenGL 4.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Enable Multisample anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, cfg.windowSamples);

	glfwSetErrorCallback(glfwErrorCallback);

	//Create window
	mWindowWidth = cfg.windowWidth;
	mWindowHeight = cfg.windowHeight;

	GLFWwindow* window = glfwCreateWindow(mWindowWidth,
		mWindowHeight,
		cfg.windowTitle.c_str(),
		nullptr,
		nullptr);
	if (!window)
	{
		fprintf(stderr, "ERROR: Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make the context of the window be the main context of current thread
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	gladLoadGL();

	glViewport(0, 0, cfg.windowWidth, cfg.windowHeight);

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

void OpenGLContext::setViewport(int setWindowWidth, int setWindowHeight)
{
	glViewport(0, 0, setWindowWidth, setWindowHeight);
}

/* Updates and returns the height of the window*/
unsigned int OpenGLContext::getWindowHeight()
{
	glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	return mWindowHeight;
}

/* Updates and returns the width of the window*/
unsigned int OpenGLContext::getWindowWidth()
{
	glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
	return mWindowWidth;
}

OpenGLContext::~OpenGLContext()
{
	// Delete all of GLFW's allocated resources
	glfwTerminate();
}

void OpenGLContext::processKeyboardInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}
}



// GLFW window callback functions for handling mouse position input
void mouseCallback(GLFWwindow* window, double x, double y)
{
	camera.handleCursorPosInput(x, y);
	//glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

// GLFW window callback functions for handling mouse button input
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	camera.handleMouseButtonInputs(button, action);
}

// GLFW window callback functions for handling keyboard button input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	camera.handleKeyboardInputs(key, action);
}