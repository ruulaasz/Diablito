#include "Material.h"

Material::Material()
{
  for (int i = 0; i < TextureType_MAXTEXTURES; i++)
  {
  	m_textures[i] = nullptr;
  }
}

Material::~Material()
{

}