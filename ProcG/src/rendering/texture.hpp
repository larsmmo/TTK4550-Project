#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

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

	bool mipMapping = true;

public:
	Texture();
	~Texture();

	void generate(unsigned int height, unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data);

	void bind(int unit = -1);
	void unbind();

	void setWrapping(GLenum mode, bool bind = false);
	void setMipMapping(bool mipMap);

	unsigned int getID();
};


#endif