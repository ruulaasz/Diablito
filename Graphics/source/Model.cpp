#include "Model.h"
#include "GraphicManager.h"

Model::Model()
{
	
}

Model::~Model()
{

}

void Model::assignMeshMaterial(Material* _material, unsigned int _index)
{
  if (!_material)
  {
  	throw "NullPointer _material";
  }

  if (_index >= 0 && _index < m_meshes.size())
  {
  	m_meshes.at(_index)->assignNewMaterial(_material);
  }
}

void Model::assignMeshTexture(Texture * _texture, TextureType _textureType, unsigned int _index)
{
  if (!_texture)
  {
  	throw "NullPointer _texture";
  }

  if (_index >= 0 && _index < m_meshes.size())
  {
  	m_meshes.at(_index)->assignNewTexture(_texture, _textureType);
  }
}

void Model::render(const GraphicDeviceContext* _immediateContext)
{
  for (uint i = 0; i < m_meshes.size(); i++)
  {
  	m_meshes.at(i)->render(_immediateContext);
  }
}