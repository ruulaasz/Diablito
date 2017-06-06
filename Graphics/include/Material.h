#pragma once
#include "Omicron_Math.h"
#include <types.h>
#include "FragmentShader.h"
#include "VertexShader.h"
#include <scene.h>

using namespace OmicronSDK;

enum TextureType
{
	TextureType_NONE =0,
	TextureType_DIFFUSE,
	TextureType_SPECULAR,
	TextureType_AMBIENT,
	TextureType_EMiSSIVE,
	TextureType_HEIGHT,
	TextureType_NORMALS,
	TextureType_SHININESS,
	TextureType_OPACITY,
	TextureType_DISPLACEMENT,
	TextureType_LIGHTMAP,
	TextureType_REFLECTION,
	TextureType_MAXTEXTURES
};

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

	ID3D11ShaderResourceView* m_textures[TextureType_MAXTEXTURES];
};