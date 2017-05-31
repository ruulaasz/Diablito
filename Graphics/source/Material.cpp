#include "Material.h"

Material::Material()
{
	for (int i = 0; i < aiTextureType_UNKNOWN; i++)
	{
		m_textures[i] = NULL;
	}

	m_vertexShader = NULL;
	m_pixelShader = NULL;
}

Material::~Material()
{

}

void Material::createMaterial(aiMaterial * _Material, FragmentShader * _PixelShader, VertexShader * _VertexShader)
{
	aiColor3D Color;
	m_vertexShader = _VertexShader;
	m_pixelShader = _PixelShader;

	if (AI_SUCCESS == _Material->Get(AI_MATKEY_COLOR_AMBIENT, Color))
	{
		m_AmbientColor.X = Color.r;
		m_AmbientColor.Y = Color.g;
		m_AmbientColor.Z = Color.b;
	}

	if (AI_SUCCESS == _Material->Get(AI_MATKEY_COLOR_DIFFUSE, Color))
	{
		m_Diffuse.X = Color.r;
		m_Diffuse.Y = Color.g;
		m_Diffuse.Z = Color.b;
	}

	if (AI_SUCCESS == _Material->Get(AI_MATKEY_COLOR_EMISSIVE, Color))
	{
		m_Emissive.X = Color.r;
		m_Emissive.Y = Color.g;
		m_Emissive.Z = Color.b;
	}

	if (AI_SUCCESS == _Material->Get(AI_MATKEY_COLOR_SPECULAR, Color))
	{
		m_Specular.X = Color.r;
		m_Specular.Y = Color.g;
		m_Specular.Z = Color.b;
	}

	if (AI_SUCCESS == _Material->Get(AI_MATKEY_COLOR_REFLECTIVE, Color))
	{
		m_Reflective.X = Color.r;
		m_Reflective.Y = Color.g;
		m_Reflective.Z = Color.b;
	}
}
