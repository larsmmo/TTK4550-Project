#include "shader.hpp"

/* Helper function that creates a shader from a filename */
GLuint createShaderObject(std::string const& filename)
{
	// Create shader type by looking at file extension
	auto idx = filename.rfind(".");
	auto extension = filename.substr(idx + 1);
	if (extension == "comp") return glCreateShader(GL_COMPUTE_SHADER);
	else if (extension == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
	else if (extension == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
	else if (extension == "tes")  return glCreateShader(GL_TESS_EVALUATION_SHADER);
	else if (extension == "vert") return glCreateShader(GL_VERTEX_SHADER);
	else if (extension == "tcs")  return glCreateShader(GL_TESS_CONTROL_SHADER);
	else						  return false;
}

void ProcG::Shader::attach(std::string const& filename)
{
	// Load the GLSL Shader from the file
	std::ifstream fd(filename.c_str());
	if (fd.fail())
	{
		fprintf(stderr,
			"SHader file could not be attached at \"%s\".\n"
			"Check if the file exists.\n",
			filename.c_str());
		return;
	}
	auto ShaderSrc = std::string(std::istreambuf_iterator<char>(fd), (std::istreambuf_iterator<char>()));

	// Create the shader object
	const char* source = ShaderSrc.c_str();
	auto shader = createShaderObject(filename);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Display errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &mStatus);
	if (!mStatus)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &mLength);
		std::unique_ptr<char[]> buffer(new char[mLength]);
		glGetShaderInfoLog(shader, mLength, nullptr, buffer.get());
		fprintf(stderr, "%s\n%s", filename.c_str(), buffer.get());
	}

	assert(mStatus);

	// Attach shader and free allocated memory
	glAttachShader(mShaderProgram, shader);
	glDeleteShader(shader);
}

void ProcG::Shader::link()
{
	// Link all attached shaders
	glLinkProgram(mShaderProgram);

	// Display errors
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &mStatus);
	if (!mStatus)
	{
		glGetProgramiv(mShaderProgram, GL_INFO_LOG_LENGTH, &mLength);
		std::unique_ptr<char[]> buffer(new char[mLength]);
		glGetProgramInfoLog(mShaderProgram, mLength, nullptr, buffer.get());
		fprintf(stderr, "%s\n", buffer.get());
	}
	assert(mStatus);
}

void ProcG::Shader::makeBasicShader(std::string const& vertexFilename,
	std::string const& fragmentFilename,
	std::string const& geometryFilename)
{
	attach(vertexFilename);
	attach(geometryFilename);
	attach(fragmentFilename);
	link();
}

GLint ProcG::Shader::getUniformFromName(std::string const& uniformName) 
{
	return glGetUniformLocation(this->get(), uniformName.c_str());
}

void ProcG::Shader::setUniform1fv(std::string const& uniformName, int count, const float* value)
{
	glUniform1fv(getUniformFromName(uniformName), count, value);
}

void ProcG::Shader::setUniform2fv(std::string const& uniformName, int count, const float* value)
{
	glUniform2fv(getUniformFromName(uniformName), count, value);
}

void ProcG::Shader::setUniform3fv(std::string const& uniformName, int count, const float* value)
{
	glUniform3fv(getUniformFromName(uniformName), count, value);
}

bool ProcG::Shader::isValidProgram()
{
	// Validate linked shader program
	glValidateProgram(mShaderProgram);

	// Display errors
	glGetProgramiv(mShaderProgram, GL_VALIDATE_STATUS, &mStatus);
	if (!mStatus)
	{
		glGetProgramiv(mShaderProgram, GL_INFO_LOG_LENGTH, &mLength);
		std::unique_ptr<char[]> infoLog(new char[mLength]);
		glGetProgramInfoLog(mShaderProgram, mLength, nullptr, infoLog.get());
		fprintf(stderr, "%s\n", infoLog.get());
		return false;
	}
	return true;
}