// System headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"

#include <cstdlib>
#include <string>
#include <assert.h>
#include <vector>

Texture::Texture()
{

}

Texture::~Texture()
{

}


void Texture::generate(unsigned int height, unsigned int width, GLenum internalFormat, GLenum format, GLenum type, bool mipMapping, unsigned char* data)
{
	if (data)
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
		// Move texture data to GPU memory
		glTexImage2D(mSampler, 0, internalFormat, width, height, 0, format, type, data);

		// Set parameters
		glTexParameteri(mSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(mSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(mSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// Bilinear texture filtering disabled
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_S, mWrapS);
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_T, mWrapT);

		if (mipMapping)
			glGenerateMipmap(mSampler);
		unbind();
	}
	else
	{
		printf("Loading of 2D texture failed. No data found");
	}
}

void Texture::generate(unsigned int height, unsigned int width, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, bool mipMapping, unsigned char* data)
{
	if (data)
	{
		glGenTextures(1, &mID);

		mSampler = GL_TEXTURE_3D;
		mInternalFormat = internalFormat;
		mFormat = format;
		mType = type;

		mHeight = height;
		mWidth = width;
		mDepth = depth;

		assert(mSampler == GL_TEXTURE_3D);
		bind();
		// Move texture data to GPU memory
		glTexImage3D(mSampler, 0, internalFormat, width, height, depth, 0, format, type, data);

		// Set parameters
		glTexParameteri(mSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(mSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_S, mWrapS);
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_R, mWrapR);
		glTexParameteri(mSampler, GL_TEXTURE_WRAP_T, mWrapT);

		if (mipMapping)
			glGenerateMipmap(mSampler);
		unbind();
	}
	else
	{
		printf("Loading of 3D texture failed. No data found");
	}
}

void Texture::generateCubeMap(unsigned int height, unsigned int width, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, std::vector<unsigned char*> data)
{
	glGenTextures(1, &mID);

	mSampler = GL_TEXTURE_CUBE_MAP;
	mInternalFormat = internalFormat;
	mFormat = format;
	mType = type;

	mHeight = height;
	mWidth = width;
	mDepth = 0;

	mWrapS = GL_CLAMP_TO_EDGE;
	mWrapR = GL_CLAMP_TO_EDGE;
	mWrapT = GL_CLAMP_TO_EDGE;

	assert(mSampler == GL_TEXTURE_CUBE_MAP);
	bind();
	for (unsigned int i = 0; i < data.size(); i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, format, type, data.at(i));
	}

	glTexParameteri(mSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(mSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(mSampler, GL_TEXTURE_WRAP_S, mWrapS);
	glTexParameteri(mSampler, GL_TEXTURE_WRAP_R, mWrapR);
	glTexParameteri(mSampler, GL_TEXTURE_WRAP_T, mWrapT);
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

unsigned int Texture::getID()
{
	return mID;
}