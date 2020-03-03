#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "sceneGraph.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene
{
private:
	SceneNode* rootNode;

public:
	void updateScene();
};

#endif