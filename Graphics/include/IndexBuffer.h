#pragma once
#include "Buffer.h"
#include <scene.h>
#include <vector>

class GraphicDevice;
using std::vector;

#define CPU_ACCESS_DEFAULT	0x00000000
#define CPU_ACCESS_READ		0x00000001
#define CPU_ACCESS_WRITE	0x00000002

#define IB_CREATE_DEFAULT	0x00000004	//Default
#define IB_CREATE_STATIC	0x00000008	//Static Buffer
#define IB_CREATE_DYNAMIC	0x00000010	//Buffer dinamico

class IndexBuffer : public Buffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	virtual void destroy() override;

	//HRESULT loadIndexFromMesh(aiMesh& _mesh);
	HRESULT create(const GraphicDevice* pDevice, unsigned int creationFlags = IB_CREATE_DEFAULT | CPU_ACCESS_DEFAULT);

	void addIndex(unsigned int _index);
	size_t getIndexSize() { return m_indexArray.size(); }

private:
	vector<unsigned int> m_indexArray;
};