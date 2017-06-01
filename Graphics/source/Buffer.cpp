#include "Buffer.h"
#include "GraphicManager.h"

Buffer::Buffer()
{
	m_buffer = NULL;
}

Buffer::~Buffer()
{
	m_buffer->Release();
}

HRESULT Buffer::createDirectX(const GraphicDevice* _device, D3D11_BUFFER_DESC * _desc, D3D11_SUBRESOURCE_DATA * _initData)
{
	HRESULT hr;
	ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());
	hr = pD3DDevice->CreateBuffer(_desc, _initData, &m_buffer);

	return hr;
}