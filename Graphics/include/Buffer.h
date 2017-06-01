#pragma once
#include <d3d11.h>

struct BufferInfo
{
	D3D11_USAGE D3D11Usage = D3D11_USAGE_DEFAULT;																		/*!< Uso del bloque de memoria, por default con uso dinamico */
	unsigned int ByteWidth;																								/*!< Tamaño en la memoria */
	D3D11_BIND_FLAG BindFlags = D3D11_BIND_VERTEX_BUFFER;																/*!< Tipo de buffer, Por default Vertexbufer*/
	unsigned int CPUAccesFlag = 0;																						/*!< Nivel de acceso del CPU, por default 0, ningun acceso */
};

class Buffer
{
public:
	Buffer();
	virtual ~Buffer();

	virtual void init() {};
	virtual void destroy() {};

	ID3D11Buffer* m_buffer;
	HRESULT createBuffer(ID3D11Device* _device, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _initData = NULL);
};