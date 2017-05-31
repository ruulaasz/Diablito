#pragma once
#include "Buffer.h"
#include <Omicron_Math.h>
#include <scene.h>

using namespace OmicronSDK;

struct VertexInfo
{
	omVector4D pos;
	omVector2D tex;
	omVector3D norm;

	VertexInfo()
	{
		memset(this, 0, sizeof(VertexInfo));
	}
};

class VertexBuffer : public Buffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	virtual void init() {};
	virtual void destroy();

	VertexInfo* m_vertexInfo;
	unsigned int m_vertexNumber;

	HRESULT loadVertexFromMesh(aiMesh& _mesh);
	HRESULT createVertexBuffer(ID3D11Device* _device, BufferInfo _info);
};

