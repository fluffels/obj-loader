#ifndef MaterialTemplate_H
#define MaterialTemplate_H

#include <cstdio>
#include <cstring>
#include <unistd.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"

using glm::vec3;

/**
  * Encapsulates a Wavefront material template.
  */
class MaterialTemplate
{
   public:
      /**
        * Assigns default values.
        */
      MaterialTemplate();

      /**
        * Destructor.
        */
      ~MaterialTemplate();

      /**
        * Return the alpha value.
        *
        * @return A float between 0.0 and 1.0.
        */
      float getAlpha() const;

      /**
        * Return the ambient co-efficient.
        *
        * A three-dimensional vector with each element e in [0.0, 1.0].
        */
      const vec3& getKa() const;

      /**
        * Return the diffuse co-efficient.
        *
        * A three-dimensional vector with each element e in [0.0, 1.0].
        */
      const vec3& getKd() const;

      /**
        * Return the specular co-efficient.
        *
        * A three-dimensional vector with each element e in [0.0, 1.0].
        */
      const vec3& getKs() const;

      /**
        * Return the emission co-efficient.
        *
        * A three-dimensional vector with each element e in [0.0, 1.0].
        */
      const vec3& getKe() const;

      /**
        * Return the shininess co-efficient.
        *
        * A three-dimensional vector with each element e in [0.0, 1.0].
        */
      float getShiny() const;

      /**
        * Bind the diffuse texture.
        */
      void bindKdMap() const;

      /**
        * Update the alpha value.
        * 
        * @param alpha A float between 0.0 and 1.0.
        */
      void setAlpha(float alpha);

      /**
        * Update the ambient co-efficient.
        *
        * @param k_a A three-dimensional vector with each element e in
        * [0.0, 1.0].
        */
      void setKa(const vec3& k_a);

      /**
        * Update the diffuse co-efficient.
        *
        * @param k_d A three-dimensional vector with each element e in
        * [0.0, 1.0].
        */
      void setKd(const vec3& k_d);

      /**
        * Update the specular co-efficient.
        *
        * @param k_s A three-dimensional vector with each element e in
        * [0.0, 1.0].
        */
      void setKs(const vec3& k_s);

      /**
        * Update the emission co-efficient.
        *
        * @param k_e A three-dimensional vector with each element e in
        * [0.0, 1.0].
        */
      void setKe(const vec3& k_e);

      /**
        * Update the shininess co-efficient.
        *
        * @param A float between 0.0 and 1.0.
        */
      void setShiny(float s);

      /**
        * Load the diffuse texture.
        *
        * @param filename The file to use as source image.
        */
      void setKdMap(const string& filename);

   protected:
      /**
        * Disable the copy constructor.
        */
      MaterialTemplate(const MaterialTemplate& rhs);

      /**
        * Disable the assignment operator.
        */
      const MaterialTemplate& operator=(const MaterialTemplate& rhs);

   private:
      /** The transparency alpha. */
      float _alpha;
      /** The ambient coefficient. */
      vec3 _k_a;
      /** The diffuse coefficient. */
      vec3 _k_d;
      /** The specular coefficient. */
      vec3 _k_s;
      /** The emission coefficient. */
      vec3 _k_e;
      /** The shininess coefficient. */
      float _s;
      /** The diffuse colour map (texture). */
      Texture* _map_kd;
};

#endif

