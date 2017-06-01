#include "IndexBuffer.h"
#include "GraphicManager.h"

IndexBuffer::IndexBuffer()
{
	
}

IndexBuffer::~IndexBuffer()
{
	destroy();
}

void IndexBuffer::destroy()
{
	m_indexArray.clear();
}

//HRESULT IndexBuffer::loadIndexFromMesh(aiMesh & _mesh)
//{
//	if (&_mesh == NULL)
//		return S_FALSE;
//
//	m_indexArray.reserve(_mesh.mNumFaces * 3);
//
//	int l = 0;
//
//	for (int j = 0; j < (int)_mesh.mNumFaces; j++)
//	{
//		for (int k = 0; k < (int)_mesh.mFaces->mNumIndices; k++)
//		{
//			m_indexArray[l] = _mesh.mFaces[j].mIndices[k];
//			l++;
//		}
//	}
//
//	if (m_indexArray.empty())
//		return S_FALSE;
//
//	return S_OK;
//}

HRESULT IndexBuffer::create(const GraphicDevice* pDevice, unsigned int creationFlags)
{
	if (!m_indexArray.empty())
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		unsigned int UsageFlag = D3D11_USAGE_DEFAULT;
		if (creationFlags & IB_CREATE_STATIC) {
			UsageFlag = D3D11_USAGE_IMMUTABLE;
		}
		if (creationFlags & IB_CREATE_DYNAMIC) {
			UsageFlag = D3D11_USAGE_DYNAMIC;
		}

		unsigned int CPUAccess = 0;
		if (creationFlags & CPU_ACCESS_READ) {
			UsageFlag = D3D11_CPU_ACCESS_READ;
		}
		if (creationFlags & CPU_ACCESS_WRITE) {
			UsageFlag = D3D11_CPU_ACCESS_WRITE;
		}

		bd.Usage = static_cast<D3D11_USAGE>(UsageFlag);
		bd.ByteWidth = m_indexArray.size() * sizeof(unsigned int);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = CPUAccess;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = &m_indexArray[0];

		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(pDevice->getPtr());
		pD3DDevice->CreateBuffer(&bd, &InitData, &m_buffer);

		if (pDevice &&  pD3DDevice)
			pD3DDevice->CreateBuffer(&bd, &InitData, &m_buffer);
		else
			return S_FALSE;

		if (!m_buffer)
			return S_FALSE;

		return S_OK;
	}

	return S_FALSE;
}

void IndexBuffer::addIndex(unsigned int _index)
{
	m_indexArray.push_back(_index);
}