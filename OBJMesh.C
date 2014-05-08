#include "OBJMesh.h"

#pragma GCC diagnostic ignored "-Wunused-variable"

OBJMesh::
OBJMesh(const char* filename):
   _mt(NULL),
   _mtlibs(),
   _normals(),
   _normalIndices(),
   _texels(),
   _texelIndices(),
   _vertices(),
   _vertexIndices()
{
   bind();
   parseFile(filename);
   constructVertexBuffer();
}

OBJMesh::
OBJMesh(const OBJMesh& rhs):
   _mt(rhs._mt),
   _mtlibs(rhs._mtlibs),
   _normals(rhs._normals),
   _normalIndices(rhs._normalIndices),
   _texels(rhs._texels),
   _texelIndices(rhs._texelIndices),
   _vertices(rhs._vertices),
   _vertexIndices(rhs._vertexIndices)
{
}

OBJMesh::
~OBJMesh()
{
   vector<MaterialTemplateLibrary*>::iterator i = _mtlibs.begin();
   while (i != _mtlibs.end())
   {
      delete *i;
      i++;
   }
}

const OBJMesh& OBJMesh::
operator=(const OBJMesh& rhs)
{
   _mt = rhs._mt;
   _mtlibs = rhs._mtlibs;
   _normals = rhs._normals;
   _normalIndices = rhs._normalIndices;
   _texels = rhs._texels;
   _texelIndices = rhs._texelIndices;
   _vertices = rhs._vertices;
   _vertexIndices = rhs._vertexIndices;

   return *this;
}

void OBJMesh::
bind()
{
   Mesh::bind();

   glActiveTexture(GL_TEXTURE1);

   if (_mt != NULL)
   {
      _mt->bindKdMap();

      GLint loc = findUniform("k_a");
      glUniform3fv(loc, 1, value_ptr(_mt->getKa()));

      loc = findUniform("k_d");
      glUniform3fv(loc, 1, value_ptr(_mt->getKd()));

      loc = findUniform("k_s");
      glUniform3fv(loc, 1, value_ptr(_mt->getKs()));

      loc = findUniform("k_e");
      glUniform3fv(loc, 1, value_ptr(_mt->getKe()));

      loc = findUniform("shiny");
      glUniform1f(loc, _mt->getShiny());
   }
}

void OBJMesh::
constructVertexBuffer()
{
   bind();

   _vertexCount = (unsigned)_vertexIndices.size();
   const unsigned VERTEX_BUFFER_SIZE = _vertexCount * ELEMENTS_PER_VERTEX;
   GLfloat* vertexBuffer = new GLfloat[VERTEX_BUFFER_SIZE];

   unsigned vertex_buffer_idx = 0;
   for (unsigned index = 0; index < _vertexIndices.size(); index++)
   {
      unsigned vertex_idx = _vertexIndices[index];

      vertexBuffer[vertex_buffer_idx++] = _vertices[vertex_idx].x;
      vertexBuffer[vertex_buffer_idx++] = _vertices[vertex_idx].y;
      vertexBuffer[vertex_buffer_idx++] = _vertices[vertex_idx].z;

      unsigned normal_idx = _normalIndices[index];

      vertexBuffer[vertex_buffer_idx++] = _normals[normal_idx].x;
      vertexBuffer[vertex_buffer_idx++] = _normals[normal_idx].y;
      vertexBuffer[vertex_buffer_idx++] = _normals[normal_idx].z;

      unsigned texel_idx = _texelIndices[index];

      vertexBuffer[vertex_buffer_idx++] = _texels[texel_idx].x;
      vertexBuffer[vertex_buffer_idx++] = _texels[texel_idx].y;
      printf("Texel = (%f, %f)\n", _texels[texel_idx].x, _texels[texel_idx].y);
   }

   GLuint buffer;
   glGenBuffers(1, &buffer);

   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   glBufferData(GL_ARRAY_BUFFER, vertex_buffer_idx * (GLsizei)sizeof(GLfloat),
      vertexBuffer, GL_STATIC_DRAW);

   GLuint loc = findAttribute("position");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 
      (GLsizei)ELEMENTS_PER_VERTEX * (GLsizei)sizeof(GLfloat), 0);

   loc = findAttribute("normal");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 
      (GLsizei)ELEMENTS_PER_VERTEX * (GLsizei)sizeof(GLfloat), 
      (void*)(3 * sizeof(GLfloat)));

   loc = findAttribute("texel");
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE,
      (GLsizei)ELEMENTS_PER_VERTEX * (GLsizei)sizeof(GLfloat),
      (void*)(6 * sizeof(GLfloat)));

   delete[] vertexBuffer;
}

void OBJMesh::
parseFile(const char* path)
{
   FILE* file;
   file = fopen(path, "r");

   /* Change pwd to the file's parent, so we can use relative paths later when
      loading MTLs. */
   char* pwd = get_current_dir_name();
   char* tmp = strdup(path);
   char* sep = strrchr(tmp, '/');
   if (sep != NULL)
   {
      *sep = '\0';
      chdir(tmp);
   }

   char* line;
   char* token;
   size_t bufferSize;

   while (file && !feof(file))
   {
      line = NULL;
      getline(&line, &bufferSize, file);

      token = strtok(line, " ");
      if (token == NULL)
      { 
         break;
      }

      if (strcmp(token, "mtllib") == 0)
      {
         token = strtok(NULL, "\n");

         MaterialTemplateLibrary* temp = new MaterialTemplateLibrary(token);
         _mtlibs.push_back(temp);
      }

      if (strcmp(token, "usemtl") == 0)
      {
         token = strtok(NULL, "\n");

         bool found = false;
         vector<MaterialTemplateLibrary*>::iterator i = _mtlibs.begin();
         while (i != _mtlibs.end())
         {
            MaterialTemplateLibrary* mtl = *i;
            _mt = mtl->get(token);
            i++;
         }
      }

      if (strcmp(token, "v") == 0)
      {
         vec3 v;

         token = strtok(NULL, " ");
         sscanf(token, "%f", &v.x);

         token = strtok(NULL, " ");
         sscanf(token, "%f", &v.y);

         token = strtok(NULL, " ");
         sscanf(token, "%f", &v.z);

         _vertices.push_back(v);
      }

      if (strcmp(token, "vn") == 0)
      {
         vec3 n;

         token = strtok(NULL, " ");
         sscanf(token, "%f", &n.x);

         token = strtok(NULL, " ");
         sscanf(token, "%f", &n.y);

         token = strtok(NULL, " ");
         sscanf(token, "%f", &n.z);

         _normals.push_back(n);
      }

      if (strcmp(token, "vt") == 0)
      {
         vec2 t;

         token = strtok(NULL, " ");
         sscanf(token, "%f", &t.x);

         token = strtok(NULL, " ");
         sscanf(token, "%f", &t.y);

         _texels.push_back(t);
      }

      if (strcmp(token, "f") == 0)
      {
         for (int i = 0; i < 3; i++)
         {
            int i_v, i_n, i_t;

            token = strtok(NULL, " ");
            sscanf(token, "%d/%d/%d", &i_v, &i_t, &i_n);

            i_v = i_v < 0 ? i_v + (int)_vertices.size() : i_v;
            _vertexIndices.push_back((unsigned)i_v);

            i_t = i_t < 0 ? i_t + (int)_texels.size() : i_t;
            _texelIndices.push_back((unsigned)i_t);

            i_n = i_n < 0 ? i_n + (int)_normals.size() : i_n;
            _normalIndices.push_back((unsigned)i_n);
         }
      }
   }

   fclose(file);
   chdir(pwd);
   free(pwd);
   free(line);
}

#pragma GCC diagnostic error "-Wunused-variable"

