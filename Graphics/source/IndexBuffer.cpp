#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
	m_indexNumber = 0;
	m_indexArray = NULL;
}

IndexBuffer::~IndexBuffer()
{

}

void IndexBuffer::destroy()
{

}

HRESULT IndexBuffer::loadIndexFromMesh(aiMesh & _mesh)
{
	if (&_mesh == NULL)
		return S_FALSE;

	m_indexNumber = _mesh.mNumFaces * 3;

	m_indexArray = new unsigned int[m_indexNumber];

	int l = 0;

	for (int j = 0; j < (int)_mesh.mNumFaces; j++)
	{
		for (int k = 0; k < (int)_mesh.mFaces->mNumIndices; k++)
		{
			m_indexArray[l] = _mesh.mFaces[j].mIndices[k];
			l++;
		}
	}

	if (!m_indexArray)
		return S_FALSE;


	return S_OK;
}

HRESULT IndexBuffer::createIndexBuffer(ID3D11Device * _device, BufferInfo _info)
{
	if (m_indexArray != NULL)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = _info.D3D11Usage;
		bd.ByteWidth = _info.ByteWidth;
		bd.BindFlags = _info.BindFlags;
		bd.CPUAccessFlags = _info.CPUAccesFlag;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = *&m_indexArray;

		_device->CreateBuffer(&bd, &InitData, &m_buffer);

		if (!m_buffer)
			return S_FALSE;

		return S_OK;
	}

	return S_FALSE;
}
