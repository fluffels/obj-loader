#include "MaterialTemplate.h"

MaterialTemplate::
MaterialTemplate():
   _alpha(1.0f),
   _k_a(0.0f, 0.0f, 0.0f),
   _k_d(0.0f, 0.0f, 0.0f),
   _k_s(0.0f, 0.0f, 0.0f),
   _k_e(0.0f, 0.0f, 0.0f),
   _s(1.0f),
   _map_kd(NULL)
{
}

MaterialTemplate::
MaterialTemplate(const MaterialTemplate& rhs):
   _alpha(rhs._alpha),
   _k_a(rhs._k_a),
   _k_d(rhs._k_d),
   _k_s(rhs._k_s),
   _k_e(rhs._k_e),
   _s(rhs._s),
   _map_kd(NULL)
{
}

MaterialTemplate::
~MaterialTemplate()
{
   delete _map_kd;
   _map_kd = NULL;
}

const MaterialTemplate& MaterialTemplate::
operator=(const MaterialTemplate& rhs)
{
   _alpha = rhs._alpha;
   _k_a = rhs._k_a;
   _k_d = rhs._k_d;
   _k_s = rhs._k_s;
   _k_e = rhs._k_e;
   _s = rhs._s;
   _map_kd = NULL;

   return *this;
}

float MaterialTemplate::
getAlpha() const
{
   return _alpha;
}

const vec3& MaterialTemplate::
getKa() const
{
   return _k_a;
}

const vec3& MaterialTemplate::
getKd() const
{
   return _k_d;
}

const vec3& MaterialTemplate::
getKs() const
{
   return _k_s;
}

const vec3& MaterialTemplate::
getKe() const
{
   return _k_e;
}

float MaterialTemplate::
getShiny() const
{
   return _s;
}

void MaterialTemplate::
bindKdMap() const
{
   if (_map_kd == NULL)
   {
      printf("[ERROR] No texture assigned to this material template.\n");
   }
   else
   {
      _map_kd->bind();
   }
}

void MaterialTemplate::
setAlpha(float alpha)
{
   _alpha = alpha;
}

void MaterialTemplate::
setKa(const vec3& k_a)
{
   _k_a = k_a;
}

void MaterialTemplate::
setKd(const vec3& k_d)
{
   _k_d = k_d;
}

void MaterialTemplate::
setKs(const vec3& k_s)
{
   _k_s = k_s;
}

void MaterialTemplate::
setKe(const vec3& k_e)
{
   _k_e = k_e;
}

void MaterialTemplate::
setShiny(float s)
{
   _s = s;
}

void MaterialTemplate::
setKdMap(const string& filename)
{
   delete _map_kd;
   _map_kd = new Texture(filename);
}

