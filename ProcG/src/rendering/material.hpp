#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#pragma once

#include "rendering/shader.hpp"
#include "rendering/texture.hpp"


#include <map>

enum MaterialType
{
	MAT_DEFAULT
};


class Material
{
private:
	ProcG::Shader* mShader;

	std::map<std::string, Texture*> textures;

public:
	Material(ProcG::Shader* shader);
	~Material();

	ProcG::Shader* getShader();
	void setShader(ProcG::Shader* shader);
	void setTexture(std::string uniformName, unsigned int unit, Texture* val);
};

#endif