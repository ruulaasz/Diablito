#pragma once
#include "Omicron_Math.h"
#include <types.h>
#include "FragmentShader.h"
#include "VertexShader.h"
#include <scene.h>

using namespace OmicronSDK;

class Material
{
public:
	Material();
	~Material();

	omVector3D m_AmbientColor;
	omVector3D m_Diffuse;
	omVector3D m_Specular;
	omVector3D m_Emissive;
	omVector3D m_Reflective;

	FragmentShader* m_pixelShader;
	VertexShader* m_vertexShader;

	ID3D11ShaderResourceView* m_textures[aiTextureType_UNKNOWN];

	void createMaterial(aiMaterial* _material, FragmentShader* _pixelShader, VertexShader* _vertexShader);
};