#pragma once

#include <glm/glm.hpp>
#include <vector>

/* Mesh structure for storing attributes and indices*/
struct Mesh {
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoordinates;
    std::vector<glm::vec3> vertices;
};