#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer()
{
	m_buffer = NULL;
}

ConstantBuffer::~ConstantBuffer()
{

}

HRESULT ConstantBuffer::createConstantBuffer(ID3D11Device* _device, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _initData)
{
	HRESULT hr;

	hr = _device->CreateBuffer(_desc, _initData, &m_buffer);

	return hr;
}