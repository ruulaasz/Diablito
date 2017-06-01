#pragma once
#include <d3d11.h>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	ID3D11Texture2D* m_texture;
};