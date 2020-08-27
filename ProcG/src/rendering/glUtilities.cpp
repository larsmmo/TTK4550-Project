#include "glUtilities.h"

#include <glad/glad.h>
#include <vector>

/* Convenience function that generates buffers and fills them with attributes
   to be used in Vertex array objects */
template <class T>
unsigned int generateAttribute(int id, int elements, std::vector<T> data, bool normalize) 
{
	// Setting up buffer, binding it and copying data into it
    unsigned int bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

	// Format specification and enabling of the vertex attribute
    glVertexAttribPointer(id, elements, GL_FLOAT, normalize ? GL_TRUE : GL_FALSE, sizeof(T), 0);
    glEnableVertexAttribArray(id);

    return bufferID;
}

unsigned int generateVAO(Mesh &mesh) 
{
	// Setting up VAO
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

	// Creating attributes for vertices, normal vectors and texture coordinates
    generateAttribute(0, 3, mesh.vertices, false);
    generateAttribute(1, 3, mesh.normals, true);
    if (mesh.textureCoordinates.size() > 0) 
	{
        generateAttribute(2, 2, mesh.textureCoordinates, false);
    }

	// Setting up index buffer, binding it and copying data into it
    unsigned int idxBufferID;
    glGenBuffers(1, &idxBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    return vaoID;
}
