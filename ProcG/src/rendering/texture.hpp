#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include <vector>

class Texture
{
private:
	unsigned int mID;

	unsigned int mHeight = 0;
	unsigned int mWidth = 0;
	unsigned int mDepth = 0;

	GLenum mSampler = GL_TEXTURE_2D;
	GLenum mType = GL_UNSIGNED_BYTE;
	GLenum mInternalFormat = GL_RGBA;
	GLenum mFormat = GL_RGBA;

	// Wrapping methods for s, t and r coordinates
	GLenum mWrapS = GL_REPEAT;         
	GLenum mWrapT = GL_REPEAT;            
	GLenum mWrapR = GL_REPEAT;    

public:
	Texture();
	~Texture();

	// One generator each for 2D and 3D textures
	void generate(unsigned int height, unsigned int width, GLenum internalFormat, GLenum format, GLenum type, bool mipMapping, unsigned char* data);
	void generate(unsigned int height, unsigned int width, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, bool mipMapping, unsigned char* data);

	// Method for generating a cubemap texture from a vector containing pointers to different images
	void generateCubeMap(unsigned int height, unsigned int width, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, std::vector<unsigned char*> data);

	void bind(int unit = -1);
	void unbind();

	void setWrapping(GLenum mode, bool bind = false);

	unsigned int getID();
};


#endif