#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#pragma once

#include "sceneGraph.hpp"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Terrain
{
protected:
	Mesh mHeightMap;
	unsigned int rows;
	unsigned int cols;

public:
	Terrain(unsigned int terrainSize, std::vector<Terrain>* mergedTerrains = nullptr);
	~Terrain();

	void generateNormals(int terrainSize);

	Mesh* getHeightMap();
	unsigned int getRows();
	unsigned int getCols();

	void from_json(json const& j);
};

class Mountain : public Terrain
{
protected:
	unsigned int maxHeight;
	glm::vec2 position;
public:
	Mountain(glm::vec2 position, int rows, int cols);
	~Mountain();
};

class Lake : public Terrain
{
protected:
	unsigned int maxDepth;
	glm::vec2 position;
public:
	Lake(glm::vec2 position, int rows, int cols);
	~Lake();
};


#endif