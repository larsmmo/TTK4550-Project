#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <stack>
#include <vector>
#include <cstdio>
#include <stdbool.h>
#include <cstdlib> 
#include <ctime> 
#include <chrono>
#include <fstream>


enum SceneNodeType {
	GEOMETRY, 
	DIRECTIONAL_LIGHT, 
	POINT_LIGHT,
	SKY_BOX
};

struct SceneNode {
	SceneNode() {
		pos = glm::vec3(0, 0, 0);
		rot = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);

        refPoint = glm::vec3(0, 0, 0);
        VAOID = -1;
        VAOIndexCount = 0;

        nodeType = GEOMETRY;

	}
	SceneNodeType nodeType;

	std::vector<SceneNode*> children;
	
	// A node's position and rotation relative to its parent
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;

	// A transformation matrix representing the transformation of the node's location relative to its parent.
	glm::mat4 currentTransformationMatrix;

	glm::mat4 MVPMatrix;

	glm::vec3 refPoint;

	// Variables for rendering in OpenGL
	int VAOID;
	unsigned int VAOIndexCount;

	// Texture variables
	unsigned int textureID;
};

SceneNode* createSceneNode();
void addChild(SceneNode* parent, SceneNode* child);
void updateSceneNodeTransformations(SceneNode* node, glm::mat4 transformationThusFar, glm::mat4 VP);
