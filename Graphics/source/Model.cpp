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
	if (_index >= 0 && _index < m_meshes.size())
	{
		m_meshes.at(_index)->assignNewMaterial(_material);
	}
}

void Model::assignMeshTexture(Texture * _texture, unsigned int _slot, unsigned int _index)
{
	if (_index >= 0 && _index < m_meshes.size())
	{
		m_meshes.at(_index)->assignNewTexture(_texture, _slot);
	}
}

void Model::setTransformMatrix(aiMatrix4x4 * _transformMatrix)
{
	m_transform.m00 = _transformMatrix->a1;
	m_transform.m01 = _transformMatrix->a2;
	m_transform.m02 = _transformMatrix->a3;
	m_transform.m03 = _transformMatrix->a4;
	  				  
	m_transform.m10 = _transformMatrix->b1;
	m_transform.m11 = _transformMatrix->b2;
	m_transform.m12 = _transformMatrix->b3;
	m_transform.m13 = _transformMatrix->b4;
	  				  
	m_transform.m20 = _transformMatrix->c1;
	m_transform.m21 = _transformMatrix->c2;
	m_transform.m22 = _transformMatrix->c3;
	m_transform.m23 = _transformMatrix->c4;
	  				  
	m_transform.m30 = _transformMatrix->d1;
	m_transform.m31 = _transformMatrix->d2;
	m_transform.m32 = _transformMatrix->d3;
	m_transform.m33 = _transformMatrix->d4;
}

void Model::render(const GraphicDeviceContext* _immediateContext)
{
	//Rendereamos el mesh del modelo
	for (uint i = 0; i < m_meshes.size(); i++)
	{
		m_meshes.at(i)->render(_immediateContext);
	}
}