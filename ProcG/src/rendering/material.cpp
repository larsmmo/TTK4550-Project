// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local headers
#include "material.hpp"
#include "rendering/texture.hpp"
#include "rendering/shader.hpp"

#include <cstdlib>
#include <string>

Material::Material(ProcG::Shader* shader)
{

}

Material::~Material()
{

}


ProcG::Shader* Material::getShader()
{
	return mShader;
}
void Material::setShader(ProcG::Shader* shader)
{
	mShader = shader;
}

void Material::setTexture(std::string uniformName, unsigned int unit, Texture* val)
{
	
}