#pragma once
#ifndef WINDOWSETTINGS_H
#define WINDOWSETTINGS_H

#include <glad/glad.h>

#include <string>

const int         windowWidth = 1280;
const int         windowHeight = 720;
const std::string windowTitle = "OpenGL Window";
const GLint       windowResizable = GL_FALSE;
const int         windowSamples = 4;

#endif