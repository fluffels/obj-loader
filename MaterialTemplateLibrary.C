#include "MaterialTemplateLibrary.h"

MaterialTemplateLibrary::
MaterialTemplateLibrary(const char* filename):
   _map()
{
   FILE* file = fopen(filename, "r");
   if (file == NULL)
   {
      printf("Could not open file '%s'.\n", filename);
      exit(-1);
   }

   char* line;
   char* token;
   size_t bufferSize;
   while (!feof(file))
   {
      line = NULL;
      getline(&line, &bufferSize, file);

      token = strtok(line, " ");

      if (strcmp(token, "newmtl") == 0)
      {
         token = strtok(NULL, "\n");
         string name = token;

         MaterialTemplate* mat = new MaterialTemplate();
         float f;
         vec3 v;
         while ((getline(&line, &bufferSize, file) != -1) &&
                (strcmp(token, "newmtl") != 0))
         {
            token = strtok(line, " ");

            if (strcmp(token, "Ns") == 0)
            {
               token = strtok(NULL, "\n");
               sscanf(token, "%f", &f);
               mat->setShiny(f);
            }
            else if (strcmp(token, "Tr") == 0)
            {
               token = strtok(NULL, "\n");
               sscanf(token, "%f", &f);
               mat->setAlpha(f);
            }
            else if (strcmp(token, "Ka") == 0)
            {
               token = strtok(NULL, "\n");
               sscanf(token, "%f %f %f", &v.x, &v.y, &v.z);
               mat->setKa(v);
            }
            else if (strcmp(token, "Kd") == 0)
            {
               token = strtok(NULL, "\n");
               sscanf(token, "%f %f %f", &v.x, &v.y, &v.z);
               mat->setKd(v);
            }
            else if (strcmp(token, "Ks") == 0)
            {
               token = strtok(NULL, "\n");
               sscanf(token, "%f %f %f", &v.x, &v.y, &v.z);
               mat->setKs(v);
            }
            else if (strcmp(token, "map_Kd") == 0)
            {
               token = strtok(NULL, "\n");
               mat->setKdMap(token);
            }
         }

         _map[name] = mat;
      }
   }

   fclose(file);
}

const MaterialTemplate* MaterialTemplateLibrary::
get(const string& name)
{
   MaterialTemplate* mt = _map[name];

   if (mt == NULL)
   {
      printf("[ERROR] Could not find material template '%s'.\n", name.c_str());
   }

   return mt;
}

