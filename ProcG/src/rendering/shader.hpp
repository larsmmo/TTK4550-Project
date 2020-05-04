#ifndef SHADER_HPP
#define SHADER_HPP
#pragma once

#include <glad/glad.h>

#include <memory>
#include <fstream>
#include <string>
#include <cassert>

/* Shader class for reading shaders from files, compiling and linking them into shader programs. Also checks for errors.*/
namespace ProcG
{
	class Shader
	{
	private:
		// Disable copying and assignment
		Shader(Shader const&) = delete;
		Shader& operator = (Shader const&) = delete;

		GLuint mShaderProgram;
		GLint  mStatus;
		GLint  mLength;

	public:
		Shader() { mShaderProgram = glCreateProgram(); }

		void   activate() { glUseProgram(mShaderProgram); }
		void   deactivate() { glUseProgram(0); }
		GLuint get() { return mShaderProgram; }
		void   destroy() { glDeleteProgram(mShaderProgram); }

		/* Attaches a shader to the program */
		void attach(std::string const& filename);

		/* Links attached shaders into the shader program */
		void link();

		/* Attaches and links shaders into the shader program */
		void makeBasicShader(std::string const& vertexFilename,
			std::string const& fragmentFilename,
			std::string const& geometryFilename);

		/* Gets a uniform ID from a string of the uniform name */
		GLint getUniformFromName(std::string const& uniformName);
		void setUniform1fv(std::string const& uniformName, int count, const float* value);
		void setUniform2fv(std::string const& uniformName, int count, const float* value);
		void setUniform3fv(std::string const& uniformName, int count, const float* value);

		/* Helps with debugging the shader program*/
		bool isValidProgram();
	};
}
#endif
