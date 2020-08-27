#include "resourceManager.hpp"
#include "rendering/shader.hpp"
#include "sceneGraph.hpp"
#include "mesh.h"
#include "rendering/texture.hpp"
#include "rendering/material.hpp"
#include "stb_image.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using json = nlohmann::json;

ImageData ResourceManager::loadImageData(std::string const filename)
{
	ImageData image;
	image.data = stbi_load(filename.c_str(), &image.width, &image.height, &image.nrChannels, 0);

	if (image.data == NULL)
	{
		printf("Loading of image failed.");
	}

	return image;
}

void ResourceManager::freeImageData(unsigned char* data)
{
	stbi_image_free(data);
}

std::vector<ImageData> ResourceManager::loadSkyBoxImageData()
{
	std::vector<std::string> faces
	{
		"skyxpos.png",
		"skyxneg.png",
		"skyypos.png",
		"skyyneg.png",
		"skyzpos.png",
		"skyzneg.png"
	};

	std::vector<ImageData> cubeMapData;

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		cubeMapData.push_back(loadImageData(faces[i]));
	}

	return cubeMapData;
}

json ResourceManager::loadJson(std::string filename)
{
	std::ifstream i(filename.c_str());
	json j;
	i >> j;
	return j;
}