#include "sceneGraph.hpp"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

SceneNode* createSceneNode() {
	return new SceneNode();
}

// Add a child to a SceneNode
void addChild(SceneNode* parent, SceneNode* child) 
{
	parent->children.push_back(child);
}

// Returns the amount of children for a SceneNode
int totalChildren(SceneNode* parent) 
{
	int count = parent->children.size();
	for (SceneNode* child : parent->children) {
		count += totalChildren(child);
	}
	return count;
}

void updateSceneNodeTransformations(SceneNode* node, glm::mat4 transformationThusFar, glm::mat4 viewProjection) 
{
	glm::mat4 transformationMatrix =
		glm::translate(node->position)
		* glm::translate(node->referencePoint)
		* glm::rotate(node->rotation.y, glm::vec3(0, 1, 0))
		* glm::rotate(node->rotation.x, glm::vec3(1, 0, 0))
		* glm::rotate(node->rotation.z, glm::vec3(0, 0, 1))
		* glm::scale(node->scale)
		* glm::translate(-node->referencePoint);

	node->currentTransformationMatrix = transformationThusFar * transformationMatrix;
	node->MVPMatrix = viewProjection * node->currentTransformationMatrix;

	switch (node->nodeType) {
	case GEOMETRY: break;
	case POINT_LIGHT:break;
	case SPOT_LIGHT: break;
	}

	for (SceneNode* child : node->children) {
		updateSceneNodeTransformations(child, node->currentTransformationMatrix, viewProjection);
	}
}

// Prints the content of a SceneNode
void printNode(SceneNode* node) 
{
	printf(
		"SceneNode {\n"
		"    Children count: %i\n"
		"    Rotation: (%f, %f, %f)\n"
		"    Relative position: (%f, %f, %f)\n"
		"    Reference point: (%f, %f, %f)\n"
		"    VAO ID: %i\n"
		"}\n",
		int(node->children.size()),
		node->rotation.x, node->rotation.y, node->rotation.z,
		node->position.x, node->position.y, node->position.z,
		node->referencePoint.x, node->referencePoint.y, node->referencePoint.z, 
		node->vertexArrayObjectID);
}