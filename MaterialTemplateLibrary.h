#ifndef MATERIAL_TEMPLATE_LIBRARY_H
#define MATERIAL_TEMPLATE_LIBRARY_H

#include <cstdio>
#include <map>
#include <string>

#include "MaterialTemplate.h"

using std::map;
using std::string;

/**
  * Encapsulates a Wavefront material template library.
  */
class MaterialTemplateLibrary
{
   public:
      /**
        * Construct the material template library from the given file.
        */
      MaterialTemplateLibrary(const char* filename);

      /**
        * Get the material template with the provided name.
        */
      const MaterialTemplate* get(const string& name);

   private:
      /** Maps material names to material templates. The value part is a pointer
        since MaterialTemplates can't be copied due to the fact that they hold
        an OpenGL identifier. */
      map<string, MaterialTemplate*> _map;
};

#endif

