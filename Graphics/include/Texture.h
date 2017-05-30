#pragma once
#include <d3d11.h>

class Texture
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView* m_texture;

	 void init();
	 void destroy();
};