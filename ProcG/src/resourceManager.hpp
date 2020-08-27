#ifndef SCENE_HPP
#define SCENE_HPP
#pragma once

#include "rendering/shader.hpp"
#include "sceneGraph.hpp"
#include "mesh.h"
#include "rendering/texture.hpp"
#include "rendering/material.hpp"

#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

struct ImageData
{
	int width;
	int height;
	int nrChannels;
	unsigned char *data;
};

class ResourceManager
{
private:

public:
	// Handles loading of an image into memory using the stb_image library
	ImageData loadImageData(std::string filename);
    std::vector<ImageData> loadSkyBoxImageData();
	void freeImageData(unsigned char* data);

	json loadJson(std::string filename);

};

#endif