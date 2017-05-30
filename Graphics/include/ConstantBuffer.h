#pragma once
#include <d3d11.h>

class ConstantBuffer
{
	public:
		ConstantBuffer();
		~ConstantBuffer();

		ID3D11Buffer* m_buffer;

	HRESULT createConstantBuffer(ID3D11Device* _device, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _initData = NULL);
};