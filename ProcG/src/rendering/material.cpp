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
	m_SamplerUniforms[name].Unit = unit;
	m_SamplerUniforms[name].Texture = value;

	switch (value->Target)
	{
	case GL_TEXTURE_1D:
		m_SamplerUniforms[name].Type = SHADER_TYPE_SAMPLER1D;
		break;
	case GL_TEXTURE_2D:
		m_SamplerUniforms[name].Type = SHADER_TYPE_SAMPLER2D;
		break;
	case GL_TEXTURE_3D:
		m_SamplerUniforms[name].Type = SHADER_TYPE_SAMPLER3D;
		break;
	case GL_TEXTURE_CUBE_MAP:
		m_SamplerUniforms[name].Type = SHADER_TYPE_SAMPLERCUBE;
		break;
	}

	if (m_Shader)
	{
		m_Shader->Use();
		m_Shader->SetInt(name, unit);
	}
}