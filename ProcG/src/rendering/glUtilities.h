#ifndef GLUTILITIES_HPP
#define GLUTILITIES_HPP
#pragma once

#include "mesh.h"

/* Generates a Vertex Array Object and copies attributes from a mesh into it */
unsigned int generateVAO(Mesh &mesh);

#endif