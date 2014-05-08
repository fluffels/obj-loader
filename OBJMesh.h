#ifndef OBJ_MESH_H
#define OBJ_MESH_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MaterialTemplate.h"
#include "MaterialTemplateLibrary.h"
#include "Mesh.h"

using glm::value_ptr;
using glm::vec2;
using glm::vec3;
using std::cout;
using std::endl;
using std::ifstream;
using std::stof;
using std::stoul;
using std::streambuf;
using std::string;
using std::stringbuf;
using std::vector;

/**
 * Encapsulates a mesh loaded from an OBJ file.
 */
class OBJMesh: public Mesh
{
   public:
      /**
       * Construct the mesh from an OBJ file.
       */
      OBJMesh(const char* filename);

      /**
        * De-allocate dynamic memory.
        */
      ~OBJMesh();

      const unsigned int ELEMENTS_PER_VERTEX = 8;

   protected:
      /**
        * Disable copy constructor.
        */
      OBJMesh(const OBJMesh& rhs);

      /**
        * Disable assignment operator.
        */
      const OBJMesh& operator=(const OBJMesh& rhs);

      /**
        * Overload bind() so that textures are bound and uniforms are updated.
        */
      virtual void bind();

   private:
      /**
       * Construct / load the OpenGL vertex buffer.
       */
      void constructVertexBuffer();

      /**
       * Parse the OBJ file.
       */
      void parseFile(const char* path);

      /** The material template associated with this OBJ. */
      const MaterialTemplate* _mt;
      /** The material template libraries loaded from this file. */
      vector<MaterialTemplateLibrary*> _mtlibs;
      /** All normals. */
      vector<vec3> _normals;
      /** Normal indices. */
      vector<GLuint> _normalIndices;
      /** All texels. */
      vector<vec2> _texels;
      /** Texel indices. */
      vector<GLuint> _texelIndices;
      /** All vertices in the mesh. */
      vector<vec3> _vertices;
      /** Vertex indices. */
      vector<GLuint> _vertexIndices;
};

#endif

