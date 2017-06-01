#include "VertexBuffer.h"
#include "GraphicManager.h"

VertexBuffer::VertexBuffer()
{
	
}

VertexBuffer::~VertexBuffer()
{
	destroy();
}

void VertexBuffer::destroy()
{
	m_vertexInfo.clear();
}

//HRESULT VertexBuffer::loadVertexFromMesh(aiMesh & _mesh)
//{
//	if (&_mesh == NULL)
//		return S_FALSE;
//
//	m_vertexInfo.reserve(_mesh.mNumVertices);
//
//	VertexInfo myVertex;
//
//	for (unsigned int i = 0; i < _mesh.mNumVertices; ++i)
//	{
//		myVertex.pos.X = _mesh.mVertices[i].x;
//		myVertex.pos.Y = _mesh.mVertices[i].y;
//		myVertex.pos.Z = _mesh.mVertices[i].z;
//		myVertex.pos.W = 1;
//
//		if (_mesh.HasTextureCoords(0))
//		{
//			myVertex.tex.X = _mesh.mTextureCoords[0][i].x;
//			myVertex.tex.Y = _mesh.mTextureCoords[0][i].y;
//		}
//
//		if (_mesh.HasNormals())
//		{
//			myVertex.norm.X =_mesh.mNormals[i].x;
//			myVertex.norm.Y =_mesh.mNormals[i].y;
//			myVertex.norm.Z =_mesh.mNormals[i].z;
//		}
//
//		addVertex(myVertex);
//	}
//
//	return S_OK;
//}

HRESULT VertexBuffer::create(const GraphicDevice* pDevice, unsigned int creationFlags)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	unsigned int UsageFlag = D3D11_USAGE_DEFAULT;
	if (creationFlags & VB_CREATE_STATIC) {
		UsageFlag = D3D11_USAGE_IMMUTABLE;
	}
	if (creationFlags & VB_CREATE_DYNAMIC) {
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
	bd.ByteWidth = m_vertexInfo.size() * sizeof(VertexData);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = CPUAccess;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &m_vertexInfo[0];

	ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(pDevice->getPtr());
	if (pDevice &&  pD3DDevice)
		pD3DDevice->CreateBuffer(&bd, &InitData, &m_buffer);
	else
		return S_FALSE;

	if (!m_buffer)
		return S_FALSE;

	return S_OK;
}

void VertexBuffer::addVertex(VertexData _vertex)
{
	m_vertexInfo.push_back(_vertex);
}