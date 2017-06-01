#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Texture.h"

class GraphicDevice;

class Mesh
{
public:
	Mesh();
	~Mesh();

	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
	Material* m_Material;

	void render(ID3D11DeviceContext* _immediateContext);
	HRESULT createMesh(const GraphicDevice* pDevice, const aiMesh& _mesh);
	void assignNewTexture(Texture& _texture, FragmentShader* _pixelShader, VertexShader* _vertexShader, int _slot);
};