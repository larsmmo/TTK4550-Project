#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	int mWindowHeight;
	int mWindowWidth;
public:
	virtual unsigned int getWindowWidth() = 0;
	virtual unsigned int getWindowHeight() = 0;
	virtual void swapDrawBuffers() = 0;
	virtual void pollEvents() = 0;
	virtual bool shouldClose() = 0;
};

class GLFWWindow : Window
{
private:
	static GLFWwindow* mWindow;
public:
	unsigned int getWindowWidth();
	unsigned int getWindowHeight();
	void swapDrawBuffers();
	void pollEvents();
	bool shouldClose();
};