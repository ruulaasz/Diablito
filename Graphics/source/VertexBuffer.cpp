#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	m_vertexInfo = NULL;
	m_vertexNumber = 0;
}

VertexBuffer::~VertexBuffer()
{
	destroy();
}

void VertexBuffer::destroy()
{
	m_vertexInfo = NULL;
}

HRESULT VertexBuffer::loadVertexFromMesh(aiMesh & _mesh)
{
	if (&_mesh == NULL)
		return S_FALSE;

	m_vertexInfo = new VertexInfo[_mesh.mNumVertices];
	m_vertexNumber = _mesh.mNumVertices;

	for (int i = 0; i < (int)_mesh.mNumVertices; i++)
	{
		m_vertexInfo[i].pos.X = _mesh.mVertices[i].x;
		m_vertexInfo[i].pos.Y = _mesh.mVertices[i].y;
		m_vertexInfo[i].pos.Z = _mesh.mVertices[i].z;
		m_vertexInfo[i].pos.W = 1;

		if (_mesh.HasTextureCoords(0))
		{
			m_vertexInfo[i].tex.X = _mesh.mTextureCoords[0][i].x;
			m_vertexInfo[i].tex.Y = _mesh.mTextureCoords[0][i].y;
		}


		if (_mesh.HasNormals())
		{
			m_vertexInfo[i].norm.X =_mesh.mNormals[i].x;
			m_vertexInfo[i].norm.Y =_mesh.mNormals[i].y;
			m_vertexInfo[i].norm.Z =_mesh.mNormals[i].z;
		}
	}

	if (!m_vertexInfo)
		return S_FALSE;

	return S_OK;
}

HRESULT VertexBuffer::createVertexBuffer(ID3D11Device * _device, BufferInfo _info)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = _info.D3D11Usage;
	bd.ByteWidth = _info.ByteWidth;
	bd.BindFlags = _info.BindFlags;
	bd.CPUAccessFlags = _info.CPUAccesFlag;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = *&m_vertexInfo;

	if (_device != NULL)
		_device->CreateBuffer(&bd, &InitData, &m_buffer);
	else
		return S_FALSE;

	if (!m_buffer)
		return S_FALSE;

	return S_OK;
}