#include "terrain.hpp"
#include "sceneGraph.hpp"
#include "shapes.h"

#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Random height data generator from http://www.mbsoftworks.sk/tutorials/opengl4/016-heightmap-pt1-random-terrain/
std::vector<std::vector<float>> generateRandomHeightData()
{
	std::vector<std::vector<float>> heightData(512, std::vector<float>(512, 0.0f));

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> hillRadiusDistribution(30, 75);
	std::uniform_real_distribution<float> hillHeightDistribution(-0.5, 0.6);
	std::uniform_int_distribution<int> hillCenterRowIntDistribution(0, 512 - 1);
	std::uniform_int_distribution<int> hillCenterColIntDistribution(0, 512 - 1);

	for (int i = 0; i < 40; i++)
	{
		const auto hillCenterRow = hillCenterRowIntDistribution(generator);
		const auto hillCenterCol = hillCenterColIntDistribution(generator);
		const auto hillRadius = hillRadiusDistribution(generator);
		const auto hillHeight = hillHeightDistribution(generator);

		for (auto r = hillCenterRow - hillRadius; r < hillCenterRow + hillRadius; r++)
		{
			for (auto c = hillCenterCol - hillRadius; c < hillCenterCol + hillRadius; c++)
			{
				if (r < 0 || r >= 512 || c < 0 || c >= 512) {
					continue;
				}
				const auto r2 = hillRadius * hillRadius; 
				const auto x2x1 = hillCenterCol - c; 
				const auto y2y1 = hillCenterRow - r; 
				const auto height = float(r2 - x2x1 * x2x1 - y2y1 * y2y1);
				if (height < 0.0f) {
					continue;
				}
				const auto factor = height / r2;
				heightData[r][c] += hillHeight * factor;
				if (heightData[r][c] > 1.0f) {
					heightData[r][c] = 1.0f;
				}
			}
		}
	}
	return heightData;
}

Terrain::Terrain(const unsigned int terrainSize, std::vector<Terrain>* mergedTerrains)
{
	rows = terrainSize;
	cols = terrainSize;

	mHeightMap.vertices.reserve(terrainSize * terrainSize);
	mHeightMap.indices.reserve(terrainSize * terrainSize * 6);

	std::vector<std::vector<float>> heightData =  generateRandomHeightData();

	// Add vertices and texture coordinates to mesh
	for (int row = 0; row < terrainSize; row++)
	{
		for (int col = 0; col < terrainSize; col++)
		{
			//mHeightMap.textureCoordinates.push_back(glm::vec2(1024.0f / row, 1024.0 / col));
			mHeightMap.textureCoordinates.push_back(glm::vec2(float(row * 26)/float(rows), float(col * 26) / float(cols)));
			mHeightMap.vertices.push_back(glm::vec3(float(row), heightData[row][col] * 23, float(col)));
			// Iterate over terrains to be added
			/*
			for (int terr = 0; terr < mergedTerrains->size(); terr++)
			{
				mHeightMap.vertices.push_back(glm::vec3(float(row), heightData[row][col] + mergedTerrains[terr]->mHeightMap.indices.y, float(col)));
			}
			*/
		}
	}

	// Calculate indices and add to mesh
	for (int row = 0; row < terrainSize - 1; row++)
	{
		for (int col = 0; col < terrainSize - 1; col++)
		{
			unsigned int offset = row * terrainSize + col;
			mHeightMap.indices.push_back(offset + 0);
			mHeightMap.indices.push_back(offset + 1);
			mHeightMap.indices.push_back(offset + terrainSize);
			mHeightMap.indices.push_back(offset + 1);
			mHeightMap.indices.push_back(offset + 1 + terrainSize);
			mHeightMap.indices.push_back(offset + terrainSize);
		}
	}

	// Calculate normals and add to mesh
	for (int i = 0; i < (terrainSize - 1) * (terrainSize - 1) * 6; i = i + 3)
	{
		//printf("i = %i", i);
		glm::vec3 v0 = mHeightMap.vertices[mHeightMap.indices[i]];
		glm::vec3 v1 = mHeightMap.vertices[mHeightMap.indices[i + 1]];
		glm::vec3 v2 = mHeightMap.vertices[mHeightMap.indices[i + 2]];
		glm::vec3 v = v2 - v0;
		glm::vec3 u = v1 - v0;
		glm::vec3 normal = glm::cross(u, v);
		mHeightMap.normals.push_back(glm::normalize(normal + mHeightMap.vertices[mHeightMap.indices[i]]));
		mHeightMap.normals.push_back(glm::normalize(normal + mHeightMap.vertices[mHeightMap.indices[i + 1]]));
		mHeightMap.normals.push_back(glm::normalize(normal + mHeightMap.vertices[mHeightMap.indices[i + 2]]));
	}
}

Terrain::~Terrain()
{

}

void Terrain::generateNormals(int terrainSize)
{
	// Calculate normals and add to mesh
	for (int i = 0; i < (terrainSize - 1) * (terrainSize - 1) * 6; i = i + 3)
	{
		glm::vec3 v0 = mHeightMap.vertices[mHeightMap.indices[i]];
		glm::vec3 v1 = mHeightMap.vertices[mHeightMap.indices[i + 1]];
		glm::vec3 v2 = mHeightMap.vertices[mHeightMap.indices[i + 2]];
		glm::vec3 v = v2 - v0;
		glm::vec3 u = v1 - v0;
		glm::vec3 normal = glm::cross(u, v);
		mHeightMap.normals.push_back(glm::normalize(normal + mHeightMap.vertices[mHeightMap.indices[i]]));
		mHeightMap.normals.push_back(glm::normalize(normal + mHeightMap.vertices[mHeightMap.indices[i + 1]]));
		mHeightMap.normals.push_back(glm::normalize(normal + mHeightMap.vertices[mHeightMap.indices[i + 2]]));
	}
}

Mesh* Terrain::getHeightMap()
{
	return &mHeightMap;
}

unsigned int Terrain::getRows()
{
	return rows;
}

unsigned int Terrain::getCols()
{
	return cols;
}

/*
void Terrain::from_json(json const& j);
{
	//Moved to RM
}
*/