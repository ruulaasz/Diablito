#pragma once
#include "Buffer.h"
#include <Omicron_Math.h>
#include <scene.h>
#include <vector>

using std::vector;
using namespace OmicronSDK;

class GraphicDevice;

struct VertexData
{
	omVector4D pos;
	omVector2D tex;
	omVector3D norm;

	VertexData()
	{
		memset(this, 0, sizeof(VertexData));
	}

	VertexData(const VertexData& other) {
		memcpy(this, &other, sizeof(VertexData));
	}
};

#define CPU_ACCESS_DEFAULT	0x00000000
#define CPU_ACCESS_READ		0x00000001
#define CPU_ACCESS_WRITE	0x00000002

#define VB_CREATE_DEFAULT	0x00000004	//Default
#define VB_CREATE_STATIC	0x00000008	//Default
#define VB_CREATE_DYNAMIC	0x00000010	//Buffer dinamico

class VertexBuffer : public Buffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	virtual void destroy() override;

	//HRESULT loadVertexFromMesh(aiMesh& _mesh);
	HRESULT create(const GraphicDevice* pDevice, unsigned int creationFlags = VB_CREATE_DEFAULT | CPU_ACCESS_DEFAULT);

	void addVertex(VertexData _vertex);
	size_t getVertexSize() { return m_vertexInfo.size(); }

private:
	vector<VertexData> m_vertexInfo;
};