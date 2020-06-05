// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"

#include <cstdlib>
#include <string>
#include <assert.h>

Texture::Texture()
{

}

Texture::~Texture()
{

}


void Texture::generate(unsigned int height, unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data)
{
	glGenTextures(1, &mID);

	mInternalFormat = internalFormat;
	mFormat = format;
	mType = type;

	mHeight = height;
	mWidth = width;
	mDepth = 0;

	assert(mSampler == GL_TEXTURE_2D);
	bind();
	glTexImage2D(mSampler, 0, internalFormat, width, height, 0, format, type, data);
	glTexParameteri(mSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(mSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(mSampler, GL_TEXTURE_WRAP_S, mWrapS);
	glTexParameteri(mSampler, GL_TEXTURE_WRAP_T, mWrapT);
	if (mipMapping)
		glGenerateMipmap(mSampler);
	unbind();
}

void Texture::bind(int unit)
{
	if (unit >= 0)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
	}
	glBindTexture(mSampler, mID);
}

void Texture::unbind()
{
	glBindTexture(mSampler, 0);
}

void Texture::setWrapping(GLenum wrapping, bool bindTexture)
{
	if (bindTexture)
		bind();
	if (mSampler == GL_TEXTURE_1D)
	{
		mWrapS = wrapping;
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_S, wrapping);
	}
	else if (mSampler == GL_TEXTURE_2D)
	{
		mWrapS = wrapping;
		mWrapT = wrapping;
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_T, wrapping);
	}
}

void Texture::setMipMapping(bool mipMap)
{
	mipMapping = mipMap;
}

unsigned int Texture::getID()
{
	return mID;
}