#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>

#include <GL/glew.h>

#include "LinkError.h"

using std::cerr;
using std::endl;
using std::string;

class Mesh
{
   public:
      /**
        * Constructor.
        */
      Mesh();

      /**
        * Destructor. Deallocates memory.
        */
      virtual ~Mesh();

      /**
        * Draw the mesh.
        */
      virtual void draw();

   protected:
      /**
        * Bind to the context.
        */
      virtual void bind();

      /**
        * Helper function to find vertex attribute locations.
        *
        * @param name The attribute's name in the shader source.
        *
        * @return The attribute's location as a GLuint, or 255 if not found.
        */
      GLuint findAttribute(const char* name);

      /**
        * Helper function to find uniforms.
        * 
        * @param name The uniform's name in the shader source.
        * 
        * @return The attribute's location as a GLint, or 255 if not found.
        */
      GLint findUniform(const char* name);

      /**
        * Amount of vertices in this mesh.
        */
      unsigned _vertexCount;

   private:
      /**
        * Handle for the VAO.
        */
      GLuint _vao;
};

#endif

