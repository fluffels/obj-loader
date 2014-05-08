#include <GL/glew.h>

#include "Constants.h"
#include "Mesh.h"

Mesh::
Mesh():
   _vertexCount(0),
   _vao(0)
{
   glGenVertexArrays(1, &_vao);
   bind();
}

Mesh::
~Mesh()
{
   glDeleteVertexArrays(1, &_vao);
}

void Mesh::
draw()
{
   bind();
   glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_vertexCount);
}

void Mesh::
bind()
{
   glBindVertexArray(_vao);
}

GLuint Mesh::
findAttribute(const char* name)
{
   GLint currentProgram;
   glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
   
   GLint location = glGetAttribLocation((GLuint)currentProgram, name);

   if (location == -1)
   {
      printf("[WARNING] Could not find attribute '%s'.\n", name);
   }

   return (GLuint)location;
}

GLint Mesh::
findUniform(const char* name)
{
   GLint currentProgram;
   glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

   GLint location = glGetUniformLocation((GLuint)currentProgram, name);

   if (location == -1)
   {
      printf("[WARNING] Could not find uniform '%s'.\n", name);
   }

   return location;
}

