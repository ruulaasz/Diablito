#pragma once
#include <d3d11.h>

class GraphicDevice;

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	ID3D11Texture2D* m_texture;

	void CreateAsRenderTarget(const GraphicDevice* _device, UINT _w, UINT _h);
	void CreateAsDepthStencil(const GraphicDevice* _device, UINT _w, UINT _h, UINT _MipLevels = 1, UINT _ArraySize = 1, UINT SampleDesc = 1, UINT _CPUAccessFlags = 0, UINT _MiscFlags = 0);
};