#pragma once
#include "Buffer.h"
#include <scene.h>

class IndexBuffer : public Buffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	virtual void init() {};
	virtual void destroy();

	unsigned int* m_indexArray;
	unsigned int m_indexNumber;

	HRESULT loadIndexFromMesh(aiMesh& _mesh);
	HRESULT createIndexBuffer(ID3D11Device* _device, BufferInfo _info);
};