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

// Update transforms using transforms above in the hierarchy and a view-projection matrix
void updateSceneNodeTransformations(SceneNode* node, glm::mat4 transformationThusFar, glm::mat4 VP) 
{
	glm::mat4 transformationMatrix =
		glm::translate(node->pos)
		* glm::translate(node->refPoint)
		* glm::rotate(node->rot.y, glm::vec3(0, 1, 0))
		* glm::rotate(node->rot.x, glm::vec3(1, 0, 0))
		* glm::rotate(node->rot.z, glm::vec3(0, 0, 1))
		* glm::scale(node->scale)
		* glm::translate(-node->refPoint);

	node->currentTransformationMatrix = transformationThusFar * transformationMatrix;
	node->MVPMatrix = VP * node->currentTransformationMatrix;

	for (SceneNode* child : node->children) {
		updateSceneNodeTransformations(child, node->currentTransformationMatrix, VP);
	}
}