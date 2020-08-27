#include "shapes.h"

#define M_PI 3.14159265359f

// Inspired from https://github.com/bartvbl/TDT4230-Assignment-1/blob/master/src/utilities/shapes.cpp

Mesh cube(glm::vec3 scale, glm::vec2 textureScale, bool textureTiling, bool invert, glm::vec3 textureScale3d) {
    glm::vec3 vertices[8];
    int indices[36];

	for (int y = 0; y <= 1; y++) {
		for (int z = 0; z <= 1; z++) {
			for (int x = 0; x <= 1; x++) {
				vertices[x + y * 4 + z * 2] = glm::vec3(x * 2 - 1, y * 2 - 1, z * 2 - 1) * scale * 0.5f;
			}
		}
	}

	// Define vertices and normals for each side of the cube
    int faces[6][4] = {
        {2,3,0,1},
        {4,5,6,7}, 
        {7,5,3,1},  
        {4,6,0,2}, 
        {5,4,1,0}, 
        {6,7,2,3}, 
    };

	glm::vec3 normals[6] = {
	{ 0,-1, 0}, 
	{ 0, 1, 0}, 
	{ 1, 0, 0},
	{-1, 0, 0}, 
	{ 0, 0,-1}, 
	{ 0, 0, 1},
	};

    scale = scale * textureScale3d;
    glm::vec2 faceScale[6] = {
        {-scale.x,-scale.z}, // Bottom
        {-scale.x,-scale.z}, // Top
        { scale.z, scale.y}, // Right
        { scale.z, scale.y}, // Left
        { scale.x, scale.y}, // Back
        { scale.x, scale.y}, // Front
    }; 

    glm::vec2 UV[4] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
    };

    Mesh cube;
    for (int face = 0; face < 6; face++) {
        int offset = face * 6;
        indices[offset + 0] = faces[face][0];
        indices[offset + 3] = faces[face][0];

        if (!invert) {
            indices[offset + 1] = faces[face][3];
            indices[offset + 2] = faces[face][1];
            indices[offset + 4] = faces[face][2];
            indices[offset + 5] = faces[face][3];
        } else {
            indices[offset + 1] = faces[face][1];
            indices[offset + 2] = faces[face][3];
            indices[offset + 4] = faces[face][3];
            indices[offset + 5] = faces[face][2];
        }

        for (int i = 0; i < 6; i++) {
            cube.vertices.push_back(vertices[indices[offset + i]]);
            cube.indices.push_back(offset + i);
            cube.normals.push_back(normals[face] * (invert ? -1.f : 1.f));
        }

        glm::vec2 textureScale = textureTiling ? (faceScale[face] / textureScale) : glm::vec2(1);

        if (!invert) {
            for (int i : {1,2,3,1,0,2}) {
                cube.textureCoordinates.push_back(UV[i] * textureScale);
            }
        } else {
            for (int i : {3,1,0,3,0,2}) {
                cube.textureCoordinates.push_back(UV[i] * textureScale);
            }
        }
    }

    return cube;
}