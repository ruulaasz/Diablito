#pragma once
#include <d3d11.h>
#include <string>

using namespace std;

class GraphicDevice;

class Texture
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView* m_texture;

	void init();
	void destroy();
	void loadFromFile(GraphicDevice* _device, string _route);
};