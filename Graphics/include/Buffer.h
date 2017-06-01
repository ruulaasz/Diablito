#pragma once
#include <d3d11.h>

class GraphicDevice;

class Buffer
{
public:
	Buffer();
	virtual ~Buffer();

	virtual void init() {};
	virtual void destroy() {};

	ID3D11Buffer* m_buffer;
	virtual HRESULT createDirectX(const GraphicDevice* _device, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _initData = NULL);
};